#include "motion_processor.h"

void MotionProcessor::process(Frame& frame) {
    
    if (m_first_frame) {
        m_prev_frame = frame.data;
        m_first_frame = false;
        return;
    }
        

    if (frame.data.size() != m_prev_frame.size()) {
        Logger::write_log(Priority::error, "Frame size mismatch");
        return;
    }

    size_t diff_count = 0;

    for (size_t i = 0; i < frame.data.size(); ++i) {
        size_t d = std::abs(frame.data[i] - m_prev_frame[i]);
        if (d > 5) ++diff_count;
    }

    if (diff_count > frame.data.size() * 0.001) {
        frame.events.push_back({"Motion detected"});
    }

    m_prev_frame = frame.data;
}