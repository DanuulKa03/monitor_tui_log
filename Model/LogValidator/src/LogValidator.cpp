#include "../include/LogValidator.hpp"


void validateLog(std::istream& in){
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


			regex json_pattern("\\{.*?\\}");
			if (regex_search(match_payload, match_json, json_pattern)) {
				std::string   json_string = match_json[0];
				j = json::parse(json_string);
			}
			 else {
				j["empty"] = "json string is empty";
			}

			if(!j.empty()  &&  j.contains("empty")){
                  GetLog(match_datetime[0], match_firmware[0], match_owner[0], match_payload);
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

LogItem GetLog(std::string s_datatime, std::string s_firmware, std::string s_owner, std::string s_payload){
    LogItem item;
    item.date_time = s_datatime;
    item.firmware = s_firmware;
    item.owner = s_owner;
    item.payloadVector.push_back(std::make_pair(s_payload, PayloadType::text));
    return item;
}
