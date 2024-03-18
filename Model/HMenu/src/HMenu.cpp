//
// Created by dika on 17.03.2024.
//
#include "HMenu.hpp"

Component HMenu(std::vector<std::string> *entries, int *selected, MainWindow &win)
// возможно содание такой функции ошибка
{
    MenuOption opt =  MenuOption::Horizontal();
    opt.on_change = handleMenuClick(win);

    return Menu(entries, selected, opt);
}