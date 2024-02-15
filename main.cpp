#include "Model/MainWindow/include/MainWindow.h"
#include <string>
#include <fstream>
#include <iostream>
#include <regex>

enum class Token {
    DateTime,
    Firmware,
    Owner,
    Payload
};



std::ifstream openFile(const std::string& filename) {
    std::ifstream file(filename);
    
}

void fileValidator (std::ifstream& in){
    
    std::string line;

    if (in.is_open())
    {

        std::smatch match_datetime;
        std::smatch match_firmware;
        std::smatch match_owner;

        // паттерны полей полезной информации из строки
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

void processArguments(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Err" << std::endl;
        return;
    }

    std::string filename = argv[2];
    std::cout << "File: " << filename  << std::endl;
    std::ifstream in(filename);

    fileValidator(in); 
     
}



int main(int argc, char* argv[]) {
    MainWindow app;
  //  app.Run();
    processArguments(argc, argv); 
    return 0;

}

