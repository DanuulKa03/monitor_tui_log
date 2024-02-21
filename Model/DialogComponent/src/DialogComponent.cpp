//
// Created by dika on 12.02.2024.
//

#include "../include/DialogComponent.hpp"

Component DialogComponent(std::string &filePath, std::function<void()> do_nothing, std::function<void()> hide_modal)
{
    auto component = Container::Vertical({
        Input(filePath, "Path to file"),
        Renderer([] { return separator(); }),
        Button("Save", do_nothing),
        Button("Quit modal", hide_modal),
    });
    // Polish how the two buttons are rendered:
    component |= Renderer([&](Element inner) {
        return vbox({
            text("Save file"),
            separator(),
            inner,
        }) | size(WIDTH, GREATER_THAN, 30) | border;
    });
    return component;
}