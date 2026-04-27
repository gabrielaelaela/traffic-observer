#include "pipeline.h"

void Pipeline::setReader(std::unique_ptr<IVideoReader> reader) {
    m_reader = std::move(reader);
}

void Pipeline::addProcessor(std::unique_ptr<IProcessor> processor) {
    m_processors.push_back(std::move(processor));
}

void Pipeline::addOutput(std::unique_ptr<IOutput> output) {
    m_outputs.push_back(std::move(output));
}

void Pipeline::run() {
    if (!m_reader || !m_reader->start()) return;

    Frame frame;
    while (m_reader->read(frame)) {
        frame.events.clear();

        for (auto& p: m_processors) {
            p->process(frame);
        }

        for (auto& o: m_outputs) {
            o->send(frame);
        }
    }
}