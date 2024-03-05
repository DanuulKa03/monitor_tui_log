//
// Created by dika on 29.02.2024.
//

#ifndef LOG_MONITOR_LOGITEM_HPP
#define LOG_MONITOR_LOGITEM_HPP

#include <string>
#include <map>

enum class PayloadType {
    text,
    json,
    code
};

class LogItem
{
public:

    LogItem(std::string date_time, std::string firmware, std::string owner, std::string payload,
            std::map<std::string, PayloadType> payloadMap  = std::map<std::string, PayloadType>());

    std::string date_time;
    std::string firmware;
    std::string owner;
    std::string payload;
    std::map<std::string, PayloadType> payloadMap;
};

#endif //LOG_MONITOR_LOGITEM_HPP