//
// Created by dika on 12.02.2024.
//

#include "DialogComponent.hpp"

#include <utility>

Component DialogComponent(std::string &filePath, std::function<void()> do_nothing, std::function<void()> hide_modal)
{
    auto component = Container::Vertical({
        Input(filePath, "Path to file"),
        Renderer([] { return separator(); }),
        Button("Save", std::move(do_nothing)),
        Button("Quit modal", std::move(hide_modal)),
    });
    // Polish how the two buttons are rendered:
    component |= Renderer([&](Element inner) {
        return vbox({
            text("Save file"),
            separator(),
            std::move(inner),
        }) | size(WIDTH, GREATER_THAN, 30) | border;
    });
    return component;
}