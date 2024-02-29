#include "Model/MainWindow/include/MainWindow.h"
#include <string>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <boost/tokenizer.hpp>
#include <boost/regex.hpp>
#include <boost/json.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using regex = boost::regex;
using smatch = boost::smatch;


json getJSON(std::string match_payload, smatch& match_json){
	regex json_pattern("\\{.*?\\}");
	if (regex_search(match_payload, match_json, json_pattern)){
		std::string json_string = match_json[0]; 
		json j = json::parse(json_string);
		return j;
	} 
	json error_json;
    error_json["empty"] = "json string is empty";
    return error_json;
}

void fileValidator (std::istream& in){
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
			boost::smatch match_json;

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


int main(int argc, char* argv[]) {
    int prog_opt;
    std::string filename;
    std::ifstream in;
    bool read_from_file = false;

    MainWindow app;
   // app.Run();

    while ((prog_opt = getopt(argc, argv, "f:")) != -1) {
        switch (prog_opt) {
            case 'f':
                filename = optarg;
                in.open(filename);
                if (!in.is_open()) {
                    std::cerr << "Error: Could not open file: " << filename << std::endl;
                    return 1;
                }
				
               read_from_file = true;
				
               break;

            case 'l':

            default:
                std::cerr << "Usage: " << argv[0] << " [-f|--file filename" << std::endl;
                return 1;
        }
        
    }

    if (!read_from_file) {
        std::string line;
		fileValidator(std::cin);
    } else {
		if (in.is_open()){
            fileValidator(in); 
			in.close();
		}

    }
    return 0;

}

