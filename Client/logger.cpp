//
// Created by ts on 18-2-7.
//


#include <cstdlib>
#include <time.h>
#include "logger.h"

std::ofstream Logger::m_error_log_file;
std::ofstream Logger::m_info_log_file;
std::ofstream Logger::m_warn_log_file;

void initLogger(const std::string& info_log_filename,
    const std::string& warn_log_filename,
    const std::string& error_log_filename) {
    Logger::m_info_log_file.open(info_log_filename.c_str(), std::ios::app);//在文件末尾添加内容
    Logger::m_warn_log_file.open(warn_log_filename.c_str(), std::ios::app);
    Logger::m_error_log_file.open(error_log_filename.c_str(), std::ios::app);
}

std::ostream& Logger::getStream(log_rank_t log_rank) {
    return (log_rank :: INFO == log_rank) ?
               (m_info_log_file.is_open() ? m_info_log_file : std::cout) :
           (log_rank::WARNING == log_rank ?
               (m_warn_log_file.is_open() ? m_warn_log_file : std::cerr) :
              (m_error_log_file.is_open() ? m_error_log_file : std::cerr));
}

std::ostream& Logger::start(log_rank_t log_rank,
    const int line,
    const std::string& function)
{
    time_t time_seconds = time(0);
    struct tm nowtime;
    //time(&time_seconds);
    char time_string[128];
    //ctime_r(&tm, time_string);
    localtime_s(&nowtime, &time_seconds);
    strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", &nowtime);
    return getStream(log_rank) << time_string
        << "    function (" << function << ")"
        << "    line " << line << "    "
        << std::flush;
}

Logger::~Logger() {
    getStream(m_log_rank) << std::endl << std::flush;

    if (log_rank::FATAL == m_log_rank) {
        m_info_log_file.close();
        m_info_log_file.close();
        m_info_log_file.close();
        abort();
    }
}