#include "Model/MainWindow/include/MainWindow.h"
#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include <unistd.h>

enum class Token {
    DateTime,
    Firmware,
    Owner,
    Payload
};


// отслеживать json
void fileValidator (std::ifstream& in){
    std::string line;
    if (in.is_open())
    {

        std::smatch match_datetime;
        std::smatch match_firmware;
        std::smatch match_owner;

        // паттерны полей полезной информации из строки
        // boost instead of regex
        // function getopt() <getopt.h> for argument 
        std::regex pat_datetime("\\[(\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2})\\] ");
        std::regex pat_firmware("\\(Firmware:(Info|Debug|Warning|Critical|Fatal)\\) ");
        std::regex pat_owner("\\b(\\w+): ");

        while (std::getline(in, line))
        {
            if (std::regex_search(line, match_datetime, pat_datetime)
                && std::regex_search(line, match_firmware, pat_firmware)
                && std::regex_search(line, match_owner, pat_owner)) {
                
                std::string match_payload = match_owner.suffix(); // собираем подстроку после последнего совпадения в осташейся строке
               std::cout << "Useful part: " << match_datetime.str() 
                         << match_firmware.str() << match_owner.str()
                         << match_payload << std::endl;

                Token token = Token::Firmware;
                   /* if (std::regex_search(line, match_datetime, pat_datetime)) {
                        token = Token::DateTime;
                    } else if (std::regex_search(line, match_firmware, pat_firmware)) {
                        token = Token::Firmware;
                    } else if (std::regex_search(line, match_owner, pat_owner)) {
                        token = Token::Owner;
                    } else {
                        token = Token::Payload;
                }*/

              //  std::cout << "Token: " << static_cast<int>(token) << std::endl;

            } else {
                std::cout << "Useful part not found." << std::endl;
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

