cmake_minimum_required(VERSION 3.10)
project(TrafficObserver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

find_package(Boost REQUIRED COMPONENTS log log_setup)

add_executable(TrafficObserver 
    src/main.cpp 
    src/services/video_ingest/opencv_reader.cpp 
    src/logger/logger.cpp
    src/processors/grayscale/grayscale_processor.cpp
    src/core/pipeline/pipeline.cpp
    src/processors/motion/motion_processor.cpp
)

target_include_directories(TrafficObserver PRIVATE src)

target_link_libraries(TrafficObserver 
    ${OpenCV_LIBS} 
    Boost::log 
    Boost::log_setup
)
