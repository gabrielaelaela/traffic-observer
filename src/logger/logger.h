#pragma once
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <string>

enum Priority {trace, debug, info, warning, error, fatal};

class Logger {
public:
    inline static std::string filename = "sample.log";
    static void write_log(const Priority& p, const std::string& msg);

private:
    Logger();
    inline static bool m_isDeclared = false;

};
