#pragma once

#include <memory>
#include <vector>
#include <thread>
#include "services/video_ingest/ivideo_reader.h"
#include "core/frame.h"
#include "core/pipeline/iprocessor.h"
#include "core/pipeline/ioutput.h"
#include "core/utils/thread_safe_queue.h"

class ThreadedPipeline {
public: 
    void setReader(std::unique_ptr<IVideoReader> reader);
    void addProcessor(std::unique_ptr<IProcessor> processor);
    void addOutput(std::unique_ptr<IOutput> output);
    void run();

private:
    std::unique_ptr<IVideoReader> m_reader;
    std::vector<std::unique_ptr<IProcessor>> m_processors;
    std::vector<std::unique_ptr<IOutput>> m_outputs;

    ThreadSafeQueue<std::shared_ptr<Frame>> m_queueReader;
    ThreadSafeQueue<std::shared_ptr<Frame>> m_queueProcessor;

    void read();
    void process();
    void output();
};