#include "Model/MainWindow/include/MainWindow.h"
#include <string>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <boost/tokenizer.hpp>
#include "Model/LogValidator/include/LogValidator.hpp"


int main(int argc, char* argv[]) {
    int prog_opt;
    std::string filename;
    std::ifstream in;
    bool read_from_file = false;

    MainWindow app(1);

    while ((prog_opt = getopt(argc, argv, "f:l")) != -1) {
        switch (prog_opt) {
            case 'f':
                filename = optarg;
                in.open(filename);
                if (!in.is_open()) {
                    std::cerr << "Error: Could not open file: " << filename << std::endl;
                    return 1;
                }

                validateLog(in, app.getItemsWindow()[0].getBufferLogs());
                in.close();
                break;

            case 'l':
                validateLog(std::cin, app.getItemsWindow()[0].getBufferLogs());
                break;

            default:
                std::cerr << "Usage: " << argv[0] << " [-f|--file filename or [-l]--live " << std::endl;
                return 1;
        }

    }

    app.Run();
    return 0;
}

