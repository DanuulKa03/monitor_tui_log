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

    const int sizeCapacity = 100;
    boost::circular_buffer<LogItem> bufferLogs;

//    bool appendLogToWindow(LogItem& item);

    bool appendLogToWindow(LogItem& item);

};

#endif

