#include "../include/LogValidator.hpp"
#include "../../JsonParser/include/getJson.hpp"

void LogValidator::validateLog(std::istream& in){
//void validateLog(std::istream& in){
    std::string line;
        regex datetime_pattern("\\[(\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2})\\] ");
        regex firmware_pattern("\\(Firmware:(Info|Debug|Warning|Critical|Fatal)\\) ");
        regex owner_pattern("\\b(\\w+): ");

        smatch match_datetime;
        smatch match_firmware;
        smatch match_owner;
        while (std::getline(in, line)){

                if (regex_search(line, match_datetime, datetime_pattern)
                        && regex_search(line, match_firmware, firmware_pattern)
                        && regex_search(line, match_owner, owner_pattern)) {

                        std::string match_payload = match_owner.suffix(); 
                        smatch match_json;

                        json j;
                        j = getJSON(match_payload, match_json); 

                        if(!j.empty() && j.contains("empty")){
                                        std::cout << "USEFUL PART1: " << match_datetime[0]
                                          << match_firmware[0] << match_owner[0]
                                          << match_payload << std::endl;

                        }

                        else{
                        std::cout << "USEFUL PART2: " << match_datetime[0]
                                          << match_firmware[0] << match_owner[0]
                                          << match_json.prefix() << std::setw(4) << j
                                          << match_json.suffix() << std::endl;
                        }
                }
        }
}


