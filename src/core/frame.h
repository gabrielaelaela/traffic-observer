#pragma once
#include <vector>
#include <string>

struct Event {
    std::string type;
};

struct Frame {
    int width = 0;
    int height = 0;
    int channels = 3;
    std::vector<unsigned char> data;
    std::vector<Event> events;
};