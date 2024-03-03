//
// Created by dika on 29.02.2024.
//

#ifndef LOG_MONITOR_LOGITEM_HPP
#define LOG_MONITOR_LOGITEM_HPP

#include <string>

class LogItem
{
public:

    LogItem(std::string date_time, std::string firmware, std::string owner, std::string payload);
    const std::string date_time;
    const std::string firmware;
    const std::string owner;
    const std::string payload;
};

#endif //LOG_MONITOR_LOGITEM_HPP