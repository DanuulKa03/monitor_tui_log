//
// Created by dika on 11.03.2024.
//

#ifndef TABCONTROLLER_HPP
#define TABCONTROLLER_HPP

#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include <boost/circular_buffer.hpp>

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"
#include "../../LogItem/include/LogItem.hpp"
#include "../../Json/include/json.hpp"
#include "../../MyCollapsible/include/MyCollapsible.hpp"

using JSON = nlohmann::json;
using namespace ftxui;

class TabController
{
public:
    TabController();

    // Копирующий конструктор
    TabController(const TabController& other) {
        keyFilter = other.keyFilter;
        containerLog = other.containerLog;
        bufferLogs = other.bufferLogs;
    }

    // Оператор присваивания
    TabController& operator=(TabController other) {
        // Обмен значений текущего объекта и объекта, переданного в параметре,
        // с использованием копирующего конструктора
        std::swap(*this, other);
        return *this;
    }

    std::string keyFilter;

    Component containerLog = Container::Vertical({});; //окно логов программы

    boost::circular_buffer<LogItem> &getBufferLogs();

    bool appendLogToWindow(LogItem &item);

private:
    const int sizeCapacity = 100; //кол-во элементов в буфере

    boost::circular_buffer<LogItem> bufferLogs; //кольцевой буфер в котором хранятся логи
    static Component Inner(std::vector<Component> children);
};
#endif //TABCONTROLLER_HPP
