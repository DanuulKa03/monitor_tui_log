#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <string>
#include <vector>
#include <boost/circular_buffer.hpp>

#include "../../DialogComponent/include/DialogComponent.hpp"
#include "../../MyCollapsible/include/MyCollapsible.hpp"
#include "../../Json/include/json.hpp"
#include "../../LogItem/include/LogItem.hpp"

class MainWindow {
public:
    //TODO Написать класс, который будет принимать число логов в конструкторе и обрабатывать это
    MainWindow();
    void Run();
    void Render();

    Component& getContainerLog()
    {
        return containerLog;
    }

private:
    std::string title_;
    Component containerLog;

    //TODO по идеи, при запуске программы, мы можем посчитать сколько будет файлов или потоков и при
    // создании экземпляра класса сразу заполнить

    std::vector<std::string> tab_titles;
    int selected_tab = 0;

    const int sizeCapacity = 100;
    boost::circular_buffer<LogItem> bufferLogs;

    bool appendLogToWindow(LogItem& item); //добавляет логи в окно containerLog

    std::function<void()> filterOwner(std::string& key); //лямбда фунция для фильтрации логов по owner

};

#endif

