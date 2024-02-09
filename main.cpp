// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
#include <functional>  // for function
#include <iostream>  // for basic_ostream::operator<<, operator<<, endl, basic_ostream, basic_ostream<>::__ostream_type, cout, ostream
#include <string>    // for string, basic_string, allocator
#include <vector>    // for vector

#include "ftxui/component/captured_mouse.hpp"      // for ftxui
#include "ftxui/component/component.hpp"           // for Menu
#include "ftxui/component/component_options.hpp"   // for MenuOption
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive

int main() {
    using namespace ftxui;

    std::vector<std::string> tab_values{
            "tab_1",
            "tab_2",
            "tab_3",
    };
    int tab_selected = 0;
    auto tab_toggle = Toggle(&tab_values, &tab_selected);

    auto layout = Container::Horizontal({
        tab_toggle,
    });

    auto component = Renderer(layout, [&] {
        return hbox({
            tab_toggle->Render(),
        });
    });

    auto screen = ScreenInteractive::Fullscreen();
    screen.Loop(component);
}
