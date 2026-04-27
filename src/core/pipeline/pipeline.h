#pragma once

#include <memory>
#include <vector>
#include "services/video_ingest/ivideo_reader.h"
#include "core/frame.h"
#include "core/pipeline/iprocessor.h"
#include "core/pipeline/ioutput.h"

class Pipeline {
public: 
    void setReader(std::unique_ptr<IVideoReader> reader);
    void addProcessor(std::unique_ptr<IProcessor> processor);
    void addOutput(std::unique_ptr<IOutput> output);
    void run();

private:
    std::unique_ptr<IVideoReader> m_reader;
    std::vector<std::unique_ptr<IProcessor>> m_processors;
    std::vector<std::unique_ptr<IOutput>> m_outputs;
};