#ifndef LOGVALIDATOR_HPP
#define LOGVALIDATOR_HPP

#include <iostream>
#include <regex>
#include <nlohmann/json.hpp>
#include <boost/regex.hpp>

using json = nlohmann::json;
using regex = boost::regex;
using smatch = boost::smatch;
/*
class LogValidator {
public:
    LogValidator();
    void validateLog(std::istream& in);

    private:
        json getJSON(std::string match_payload, smatch& match_json);
        };

        #endif // LOGVALIDATOR_H

*/
void validateLog(std::istream& in);
#endif // LOGVALIDATOR_H
