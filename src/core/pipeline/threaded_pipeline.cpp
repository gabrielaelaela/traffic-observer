#include "threaded_pipeline.h"

void ThreadedPipeline::setReader(std::unique_ptr<IVideoReader> reader) {
    m_reader = std::move(reader);
}

void ThreadedPipeline::addProcessor(std::unique_ptr<IProcessor> processor) {
    m_processors.push_back(std::move(processor));
}

void ThreadedPipeline::addOutput(std::unique_ptr<IOutput> output) {
    m_outputs.push_back(std::move(output));
}

void ThreadedPipeline::run() {
    if (!m_reader || !m_reader->start()) return;

    std::thread threadReader(&ThreadedPipeline::read, this);
    std::thread threadProcessor(&ThreadedPipeline::process, this);
    std::thread threadOutput(&ThreadedPipeline::output, this);

    threadReader.join();
    threadProcessor.join();
    threadOutput.join();
    m_reader->stop();
}

void ThreadedPipeline::read() {
    while (true) {
        auto frame = std::make_shared<Frame>();

        if (!m_reader->read(*frame)) break;
        
        m_queueReader.push(frame);
    }
    
    m_queueReader.stop();
}

void ThreadedPipeline::process() {
    std::shared_ptr<Frame> frame;
    while (m_queueReader.pop(frame)) {
        (*frame).events.clear();

        for (auto& p: m_processors) {
            p->process(*frame);
        }
        m_queueProcessor.push(frame);
    }
    m_queueProcessor.stop();
}

void ThreadedPipeline::output() {
    std::shared_ptr<Frame> frame;
    while (m_queueProcessor.pop(frame)) {
        for (auto& o: m_outputs) {
            o->send(*frame);
        }
    }
}