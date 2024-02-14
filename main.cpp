#include "Model/MainWindow/include/MainWindow.h"
#include <string>
#include <fstream>
#include <iostream>
#include <regex>

void fileValidator (std::string string){
    
}

int main(int argc, char* argv[]) {
    MainWindow app;
  //  app.Run();
    if (argc != 3) {
        std::cerr << "Err" << std::endl;
        return 1;
    }

    std::string filename = argv[2];
    std::cout << "File: " << filename  << std::endl;
    
     std::string line;
 
    std::ifstream in(filename); 
    if (in.is_open())
    {

        std::smatch match;
        std::regex pattern("\\[(\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2})\\] \\(Firmware:(Info|Debug|Warning|Critical|Fatal)\\) \\b(\\w+): ");

        while (std::getline(in, line))
        {
            if (std::regex_search(line, match, pattern)) {
                std::cout << "Useful part: " << match.str()<<  match.suffix() << std::endl;
            } else {
                std::cout << "Useful part not found." << std::endl;
            }
        }
    }
    in.close();     
    
    return 0;

}

