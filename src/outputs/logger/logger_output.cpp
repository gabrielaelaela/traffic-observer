#include "logger_output.h"

void LoggerOutput::send(const Frame& frame) {
    for (const auto& event: frame.events) {
        Logger::write_log(Priority::trace, "[EVENT] " + event.type);
    }
}