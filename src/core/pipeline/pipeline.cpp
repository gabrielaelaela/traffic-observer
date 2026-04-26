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
    DisplayOutput displayOutput;
    while (m_reader->read(frame)) {
        for (auto& p: m_processors) {
            p->process(frame);
        }
        displayOutput.send(frame);
    }
    displayOutput.send(frame);
}