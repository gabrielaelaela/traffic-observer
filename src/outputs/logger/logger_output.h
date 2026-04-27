#pragma once
#include "core/pipeline/ioutput.h"
#include "logger/logger.h"
#include <string>

class LoggerOutput: public IOutput {
    void send(const Frame& frame) override;
};