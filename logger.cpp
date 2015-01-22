#include "logger.h"
#include <iostream>
#include <ctime>
#include <memory>
#include <thread>
#include "helper.inl"

Log::Log(int type, const char *file, int line) :
    o_stream(std::cout.rdbuf()),
    m_type(type)
{
    switch (m_type) {
    case info:
        o_stream << "I";
        break;
    case error:
        o_stream << "E";
        break;
    case fatal:
        o_stream << "F";
        break;
    default:
        o_stream << "?";
        break;
    }

    std::thread::id id = std::this_thread::get_id();

    o_stream << " " << string_format("%06d %16s %3d %0x] ", clock(), file, line, id).c_str();

}

Log::~Log()
{
    o_stream << std::endl;
}
