#ifndef LOGVALIDATOR_HPP
#define LOGVALIDATOR_HPP

#include <iostream>
#include <regex>
#include <nlohmann/json.hpp>
#include <boost/regex.hpp>
#include <boost/circular_buffer.hpp>
#include "../../LogItem/include/LogItem.hpp"

using json = nlohmann::json;
using regex = boost::regex;
using smatch = boost::smatch;

void validateLog(std::istream& in, boost::circular_buffer<LogItem> &bufferLogs);

LogItem GetLog(std::string date_time, std::string firmware, std::string owner, std::string payload, PayloadType type);

bool isCode(const std::string& payload_str);

#endif // LOGVALIDATOR_HPP
