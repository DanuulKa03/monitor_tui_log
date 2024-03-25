#include "../include/LogValidator.hpp"


LogItem GetLog(std::string date_time, std::string firmware, std::string owner, std::string payload, PayloadType type){

    std::vector<std::pair<std::string, PayloadType>> payloadVector;
    switch(type) {
        case PayloadType::text:
            payloadVector.push_back(std::make_pair(payload, PayloadType::text));
        break;
        case PayloadType::json:
            payloadVector.push_back(std::make_pair(payload, PayloadType::json));
        break;
        case PayloadType::code:
            payloadVector.push_back(std::make_pair(payload, PayloadType::code));
        break;
    }      

    LogItem item(date_time, firmware, owner, payload, payloadVector);
    return item;
}

bool isCode(const std::string& payload_str) {
    boost::regex code_pattern("(cpp|h):(\\d+)");

    boost::smatch matches;
    return boost::regex_search(payload_str, matches, code_pattern);
}

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
                if (isCode(match_payload))
                  GetLog(match_datetime[0], match_firmware[0], match_owner[0], match_payload,PayloadType::code);
                else    
                  GetLog(match_datetime[0], match_firmware[0], match_owner[0], match_payload,PayloadType::text);
				/*  std::cout << "USEFUL PART1: " << match_datetime[0]
				  << match_firmware[0] << match_owner[0]
				  << match_payload << std::endl;*/

			}

			else{
                
                GetLog(match_datetime[0], match_firmware[0], match_owner[0], match_payload,PayloadType::json);
		/*	std::cout << "USEFUL PART2: " << match_datetime[0]
				  << match_firmware[0] << match_owner[0]
				  << match_json.prefix() << std::setw(4) << j
				  << match_json.suffix() << std::endl;*/
			}
		}
	}
}



