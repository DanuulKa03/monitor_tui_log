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

nlohmann::json getJSON(std::string match_payload, boost::smatch& match_json){
	boost::regex json_pattern("\\{.*?\\}");
	if (boost::regex_search(match_payload, match_json, json_pattern)){
		std::string json_string = match_json[0]; 
		nlohmann::json j = nlohmann::json::parse(json_string);
		return j;
	} 
	json error_json;
    error_json["empty"] = "json string is empty";
    return error_json;
}

using json = nlohmann::json;
void fileValidator (std::ifstream& in){
    std::string line;
    if (in.is_open())
    {
			boost::regex datetime_pattern("\\[(\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2})\\] ");
			boost::regex firmware_pattern("\\(Firmware:(Info|Debug|Warning|Critical|Fatal)\\) ");
			boost::regex owner_pattern("\\b(\\w+): ");


			boost::smatch match_datetime;
			boost::smatch match_firmware;
			boost::smatch match_owner;
			while (std::getline(in, line)){

			if (boost::regex_search(line, match_datetime, datetime_pattern)
				&& boost::regex_search(line, match_firmware, firmware_pattern)
				&& boost::regex_search(line, match_owner, owner_pattern)) {

				std::string match_payload = match_owner.suffix(); 
				// boost::regex json_pattern("\\{.*?\\}");
				boost::smatch match_json;

			//	if (boost::regex_search(match_payload, match_json, json_pattern)) {
			//		std::string json_string = match_json[0]; 
			//		nlohmann::json j = nlohmann::json::parse(json_string);
			nlohmann::json j;
			j = getJSON(match_payload, match_json); 
				if(!j.empty() && j.contains("empty")){
						std::cout << "USEFUL PART2: " << match_datetime[0]
						  << match_firmware[0] << match_owner[0]
						  << match_payload << std::endl;

								}

				else{
				std::cout << "USEFUL PART1: " << match_datetime[0]
						  << match_firmware[0] << match_owner[0]
						  << match_json.prefix() << std::setw(4) << j
						  << match_json.suffix() << std::endl;

							}
			}
		}
	}


   in.close();    
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
        while (std::getline(std::cin, line)) {
            std::cout << line << std::endl;
        }
    } else {
            fileValidator(in); 

    }


    return 0;

}

