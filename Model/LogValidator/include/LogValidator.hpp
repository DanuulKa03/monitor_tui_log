#ifndef LOGVALIDATOR_HPP
#define LOGVALIDATOR_HPP

#include <iostream>
#include <regex>
#include <nlohmann/json.hpp>
#include <boost/regex.hpp>

using json = nlohmann::json;
using regex = boost::regex;
using smatch = boost::smatch;

void validateLog(std::istream& in);
#endif // LOGVALIDATOR_HPP
