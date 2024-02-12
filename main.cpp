#include "Model/MainWindow/include/MainWindow.h"
#include <string>
#include <fstream>
#include <iostream>


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
        while (std::getline(in, line))
        {
            std::cout << line << std::endl;
        }
    }
    in.close();     


    return 0;

}

