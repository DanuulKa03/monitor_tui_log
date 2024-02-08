#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <string>

class MainWindow {
public:
    MainWindow(); 
    void Run();  
    void Render(); 
private:
    std::string title_;
};

#endif

