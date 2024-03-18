#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <string>
#include <vector>

#include "../../TabController/include/TabController.hpp"
#include "../../DialogComponent/include/DialogComponent.hpp"
#include "../../HMenu/include/HMenu.hpp"

class MainWindow
{
public:
    //TODO Написать класс, который будет принимать число логов в конструкторе и обрабатывать это
    MainWindow(size_t countTabulations);
    void Run();
private:
    std::string title_;

    std::string key;

    //TODO по идеи, при запуске программы, мы можем посчитать сколько будет файлов или потоков и при
    // создании экземпляра класса сразу заполнить

    int selected_tab = 0;
    std::vector<std::string> tab_titles; //хранит название вкладок

    std::vector<TabController> itemsWindow; //окна вкладок

    std::function<void()> showModal(bool &modal_shown); //вкл. окна

    std::function<void()> hideModal(bool &modal_shown); //выкл. окна

    std::function<void()> exportFile(); //экспорт файла

    std::function<void()> filterOwner(std::string &key); //фильтр логов

    friend std::function<void()> handleMenuClick(MainWindow &win); // клик по кнопке меню

};

#endif

