#include "logger.h"
Logger::Logger() {
    boost::log::add_file_log(filename);
    boost::log::add_common_attributes();
}

void Logger::write_log(const Priority& p, const std::string& msg) {
    if (!m_isDeclared) Logger();

    switch (p)
    {
    case trace:
        BOOST_LOG_TRIVIAL(trace) << msg << "\n";
        break;
    
    case debug:
        BOOST_LOG_TRIVIAL(debug) << msg << "\n";
        break;

    case info:
        BOOST_LOG_TRIVIAL(info) << msg << "\n";
        break;

    case warning:
        BOOST_LOG_TRIVIAL(warning) << msg << "\n";
        break;

    case error:
        BOOST_LOG_TRIVIAL(error) << msg << "\n";
        break;

    case fatal:
        BOOST_LOG_TRIVIAL(fatal) << msg << "\n";
        break;

    default:
        break;
    }
}