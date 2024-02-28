//
// Created by dika on 28.02.2024.
//

#ifndef LOG_MONITOR_BUTTON_HPP
#define LOG_MONITOR_BUTTON_HPP

#include <ftxui/component/component.hpp>
#include <functional>

ftxui::Component MyButton(const char* prefix,
                          const char* title,
                          std::function<void()>);

#endif //LOG_MONITOR_BUTTON_HPP
