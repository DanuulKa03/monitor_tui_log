#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <string>

#include "../../DialogComponent/include/DialogComponent.hpp"
#include "../../MyCollapsible/include/MyCollapsible.hpp"
#include "../../Json/include/json.hpp"
#include "../../LogItem/include/LogItem.hpp"

class MainWindow {
public:
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

    bool appendLogToWindow(LogItem& item);
};

#endif

