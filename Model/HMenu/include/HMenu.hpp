//
// Created by dika on 17.03.2024.
//

#ifndef HMENU_HPP
#define HMENU_HPP

#include "../../MainWindow/include/MainWindow.h"

using namespace ftxui;
class MainWindow;

Component HMenu(std::vector<std::string> *entries, int *selected, MainWindow &win);

#endif //HMENU_HPP
