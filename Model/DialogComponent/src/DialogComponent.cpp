//
// Created by dika on 12.02.2024.
//

#include "../include/DialogComponent.hpp"

Component DialogComponent(std::function<void()> do_nothing, std::function<void()> hide_modal)
{
    auto component = Container::Vertical({
                                                 Button("Do nothing", do_nothing),
                                                 Button("Quit modal", hide_modal),
                                         });
    // Polish how the two buttons are rendered:
    component |= Renderer([&](Element inner) {
        return vbox({
                            text("Modal component "),
                            separator(),
                            inner,
                    })                               //
               | size(WIDTH, GREATER_THAN, 30)  //
               | border;                        //
    });
    return component;
}
