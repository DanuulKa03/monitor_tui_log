//
// Created by dika on 15.02.2024.
//

#ifndef LOG_MONITOR_MYCOLLAPSIBLE_HPP
#define LOG_MONITOR_MYCOLLAPSIBLE_HPP

#include <memory>      // for shared_ptr, allocator
#include <utility>     // for move

#include "ftxui/component/component.hpp"  // for Checkbox, Maybe, Make, Vertical, Collapsible
#include "ftxui/component/component_base.hpp"  // for Component, ComponentBase
#include "ftxui/component/component_options.hpp"  // for CheckboxOption, EntryState
#include "ftxui/dom/elements.hpp"  // for operator|=, text, hbox, Element, bold, inverted
#include "ftxui/util/ref.hpp"  // for Ref, ConstStringRef

#include "../../LogItem/include/LogItem.hpp"

using namespace ftxui;

Component MyCollapsible(LogItem& item, Component child, Ref<bool> show = false);

#endif //LOG_MONITOR_MYCOLLAPSIBLE_HPP
