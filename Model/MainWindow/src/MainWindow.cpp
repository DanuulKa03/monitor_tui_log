#include "MainWindow.h"
#include <memory>  // for shared_ptr, allocator, __shared_ptr_access
#include <iostream>
#include <string> 
#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Renderer, ResizableSplitBottom, ResizableSplitLeft, ResizableSplitRight, ResizableSplitTop
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for Element, operator|, text, center, border

using namespace ftxui;
MainWindow::MainWindow() : title_("My Application") {}

void MainWindow::Run() {

    std::string key;
    Component input_key = Input(&key, "key entry field");

    auto container = Container::Horizontal({
        input_key,
    });

    auto buttonImport = Button("Import",[&] {});
    auto buttonExport = Button("Export",[&] {});

    auto containerButton = Container::Vertical({
        buttonImport,
        buttonExport,
    });

    auto features = Renderer(containerButton, [&]{
        return vbox({

            hbox({
                text("key : "),
                input_key->Render()
            }),

            separator(),

            buttonImport->Render(),
            buttonExport->Render(),

        });
    });
  
  
    auto textarea = Renderer([]{
        return text("right");
    });
  

    int size = 30;
    auto layout = ResizableSplitLeft(features, textarea, &size);

    auto component = Renderer(layout, [&] {
        return vbox({
            text("Top"),
            separator(),
            layout->Render() | flex,
                })|
            border;
        });
 
    auto screen = ScreenInteractive::Fullscreen();
    screen.Loop(component);

}