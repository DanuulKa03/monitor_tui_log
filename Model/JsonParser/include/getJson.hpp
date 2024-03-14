#ifndef JSONUTILS_HPP
#define JSONUTILS_HPP

#include <string>
#include <nlohmann/json.hpp>
#include <boost/regex.hpp>

using json = nlohmann::json;
using regex = boost::regex;
using smatch = boost::smatch;

json getJSON(std::string match_payload, smatch& match_json);

#endif  //JSONUTILS_HPP

