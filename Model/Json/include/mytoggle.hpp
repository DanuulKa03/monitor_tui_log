//
// Created by dika on 28.02.2024.
//

#ifndef LOG_MONITOR_MYTOGGLE_HPP
#define LOG_MONITOR_MYTOGGLE_HPP

#include "ftxui/component/component.hpp"

ftxui::Component MyToggle(const char* label_on,
                          const char* label_off,
                          bool* state);

#endif //LOG_MONITOR_MYTOGGLE_HPP
