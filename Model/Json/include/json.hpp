//
// Created by dika on 27.02.2024.
//

#ifndef LOG_MONITOR_JSON_HPP
#define LOG_MONITOR_JSON_HPP

#include <iostream>
#include <nlohmann/json.hpp>

#include "ftxui/component/component.hpp"  // for Renderer, ResizableSplitBottom, ResizableSplitLeft, ResizableSplitRight, ResizableSplitTop
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for Element, operator|, text, center, border
#include "expander.hpp"


using JSON = nlohmann::json;
using namespace ftxui;

bool ParseJSON(std::string input, JSON& out);

Component From(const JSON& json, bool is_last, int depth, Expander& expander);
Component FromString(const JSON& json, bool is_last);
Component FromNumber(const JSON& json, bool is_last);
Component FromBoolean(const JSON& json, bool is_last);
Component FromNull(bool is_last);
Component FromObject(Component prefix,
                     const JSON& json,
                     bool is_last,
                     int depth,
                     Expander& expander);
Component FromArrayAny(Component prefix,
                       const JSON& json,
                       bool is_last,
                       int depth,
                       Expander& expander);
Component FromArray(Component prefix,
                    const JSON& json,
                    bool is_last,
                    int depth,
                    Expander& expander);
Component FromTable(Component prefix,
                    const JSON& json,
                    bool is_last,
                    int depth,
                    Expander& expander);
Component FromKeyValue(const std::string& key,
                       const JSON& value,
                       bool is_last,
                       int depth,
                       Expander& expander);
Component Empty();
Component Unimplemented();
Component Basic(std::string value, Color c, bool is_last);

#endif //LOG_MONITOR_JSON_HPP
