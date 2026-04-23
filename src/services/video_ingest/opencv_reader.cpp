#include "opencv_reader.h"

OpenCVReader::OpenCVReader(const std::string& filename) : m_filename(filename) {}

bool OpenCVReader::start() {
    Logger::write_log(Priority::trace, "Trying to open video...");
    m_cap.open(m_filename);

    if(!m_cap.isOpened()) {
        Logger::write_log(Priority::error, "Could not open the file");
        return false;
    }

    m_started = true;
    Logger::write_log(Priority::info, "Video file opened successfully");

    return true;
}

bool OpenCVReader::read(Frame& frame) {
    if (!m_started) return false;
    if(!m_cap.isOpened()) {
        Logger::write_log(Priority::error, "The file was not opened");
        return false;
    }
    m_ret = m_cap.read(m_mat);

    if (!m_ret) return false;

    frame.width = m_mat.cols;
    frame.height = m_mat.rows;
    frame.data.assign(m_mat.data, m_mat.data + m_mat.total() * m_mat.elemSize());

    return m_ret;
}

bool OpenCVReader::display() {
    if(!m_cap.isOpened()) {
        Logger::write_log(Priority::error, "The file was not opened");
        return false;
    }

    if (m_ret) {
        cv::imshow("First frame", m_mat);
        cv::waitKey(10);
        return true;
    } else {
        Logger::write_log(Priority::error, "Could not read the frame");
        return false;
    }
    
}

void OpenCVReader::stop() {
    if(!m_cap.isOpened()) {
        return;
    }

    cv::destroyAllWindows();

    m_cap.release();
    m_started = false;
}

OpenCVReader::~OpenCVReader() {
    stop();
}