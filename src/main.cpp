#include <iostream>
#include <string>
#include <memory>
#include "services/video_ingest/opencv_reader.h"
#include "processors/grayscale/grayscale_processor.h"
#include "processors/motion/motion_processor.h"
#include "processors/yolo/yolo_processor.h"
#include "core/pipeline/threaded_pipeline.h"
#include "outputs/display/display_output.h"
#include "outputs/logger/logger_output.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Error: expected path to video file as argument\n";
        return -1;
    }

    std::string path = argv[1];

    auto cap = std::make_unique<OpenCVReader>(path);
    auto grayscale = std::make_unique<GrayscaleProcessor>();
    auto motion = std::make_unique<MotionProcessor>();
    //auto yolo = std::make_unique<YoloProcessor>("../models/yolov5n.onnx");
    auto yolo = std::make_unique<YoloProcessor>(
    "../models/yolov4-tiny.cfg",
    "../models/yolov4-tiny.weights",
    "../models/coco.names"
);
    auto displayOutput = std::make_unique<DisplayOutput>();
    auto loggerOutput = std::make_unique<LoggerOutput>();

    ThreadedPipeline pipeline;
    pipeline.setReader(std::move(cap));
    /*pipeline.addProcessor(std::move(grayscale));
    pipeline.addProcessor(std::move(motion));*/
    pipeline.addProcessor(std::move(yolo));
    pipeline.addOutput(std::move(displayOutput));
    pipeline.addOutput(std::move(loggerOutput));
    
    pipeline.run();

    return 0;
}