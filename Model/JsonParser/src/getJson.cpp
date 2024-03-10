#include "../include/getJson.hpp"

json getJSON(std::string match_payload, smatch& match_json) {
    regex json_pattern("\\{.*?\\}");
    if (regex_search(match_payload, match_json, json_pattern)) {
        std::string json_string = match_json[0];
        json j = json::parse(json_string);
        return j;
    }
    json error_json;
    error_json["empty"] = "json string is empty";
    return error_json;
}

