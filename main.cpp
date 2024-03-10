#include "Model/MainWindow/include/MainWindow.h"
#include <string>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <boost/tokenizer.hpp>
#include <boost/regex.hpp>
#include <boost/json.hpp>
#include <nlohmann/json.hpp>
#include "Model/JsonParser/include/getJson.hpp"
#include "Model/LogValidator/include/LogValidator.hpp"
using json = nlohmann::json;
using regex = boost::regex;
using smatch = boost::smatch;

/*
void logValidator (std::istream& in){
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
*/

int main(int argc, char* argv[]) {
    int prog_opt;
    std::string filename;
    std::ifstream in;
    bool read_from_file = false;

    MainWindow app;
   // app.Run();

    while ((prog_opt = getopt(argc, argv, "f:l")) != -1) {
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

    LogValidator validator;

    if (!read_from_file) {
        std::string line;
    //   logValidator(std::cin);
		validator.validateLog(std::cin);
        
    } else {
		if (in.is_open()){
         //   logValidator(in);
           validator.validateLog(in);
          // validateLog(in);
			in.close();
		}

    }
    return 0;

}

