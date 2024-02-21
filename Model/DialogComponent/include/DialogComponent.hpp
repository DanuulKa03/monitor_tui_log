//
// Created by dika on 12.02.2024.
//

#ifndef LOG_MONITOR_DIALOGCOMPONENT_HPP
#define LOG_MONITOR_DIALOGCOMPONENT_HPP

#include <ftxui/component/component_options.hpp>  // for ButtonOption
#include <ftxui/component/mouse.hpp>              // for ftxui
#include <functional>                             // for function
#include <memory>                                 // for allocator, shared_ptr

#include "ftxui/component/component.hpp"  // for Button, operator|=, Renderer, Vertical, Modal
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive, Component
#include "ftxui/dom/elements.hpp"  // for operator|, separator, text, size, Element, vbox, border, GREATER_THAN, WIDTH, center, HEIGHT

using namespace ftxui;

Component DialogComponent(std::string &filePath, std::function<void()> do_nothing, std::function<void()> hide_modal);

#endif //LOG_MONITOR_DIALOGCOMPONENT_HPP
