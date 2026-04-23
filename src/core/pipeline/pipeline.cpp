#include "pipeline.h"

void Pipeline::setReader(std::unique_ptr<IVideoReader> reader) {
    m_reader = std::move(reader);
}

void Pipeline::addProcessor(std::unique_ptr<IProcessor> processor) {
    m_processors.push_back(std::move(processor));
}

void Pipeline::run() {
    if (!m_reader || !m_reader->start()) return;

    Frame frame;
    while (m_reader->read(frame)) {
        //m_reader->display();
        for (auto& p: m_processors) {
            p->process(frame);
        }
    }
}