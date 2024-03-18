#ifndef LOGVALIDATOR_HPP
#define LOGVALIDATOR_HPP

#include <iostream>
#include <regex>
#include <nlohmann/json.hpp>
#include <boost/regex.hpp>
#include "../../LogItem/include/LogItem.hpp"

using json = nlohmann::json;
using regex = boost::regex;
using smatch = boost::smatch;

void validateLog(std::istream& in);

LogItem GetLog(std::string s_datatime, std::string s_firmware, std::string s_owner, std::string s_payload);

#endif // LOGVALIDATOR_HPP
