#pragma once
#include <string>

struct Detection {
    int x, y, w, h;
    std::string label;
    float confidence;
};