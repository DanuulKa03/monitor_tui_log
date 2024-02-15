#include <memory>  // for shared_ptr, allocator, __shared_ptr_access
#include <string>

#include "ftxui/component/component.hpp"  // for Renderer, ResizableSplitBottom, ResizableSplitLeft, ResizableSplitRight, ResizableSplitTop
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for Element, operator|, text, center, border
#include "ftxui/screen/color.hpp"
#include "MainWindow.h"
#include "../../DialogComponent/include/DialogComponent.hpp"

using namespace ftxui;

MainWindow::MainWindow() : title_("Monitor log") {}

void MainWindow::Run() {

    auto screen = ScreenInteractive::Fullscreen();

    bool modal_shown = false;
    std::string filePath; //путь до файла, который передается через диалоговое окно

    // Some actions modifying the state:
    auto show_modal = [&] { modal_shown = true; };
    auto hide_modal = [&] { modal_shown = false; };

    std::string key;
    auto input_key = Input(&key, "key entry field");

    auto buttonExport = Button("Export",show_modal);

    // for Test
    auto container = Container::Vertical({});

    auto textarea = Renderer(container,[&]{
        return vbox({
                            text("right"),
                            container->Render(),
                    });
    }) | bgcolor(Color::Red);
    auto buttonAdd = Button("Add", [&]{
        container->Add(Button("Hello", [&]{}, ButtonOption::Ascii()) | flex );
        screen.Print();
    });
    //
    auto containerButton = Container::Vertical({
        input_key,
        buttonExport,
        buttonAdd
    });

    auto features = Renderer(containerButton, [&]{
        return vbox({

            hbox({
                text("key : "),
                input_key->Render()
            }),

            separator() ,
            buttonExport->Render(),
            buttonAdd->Render(),
        });
    });

    int size = 30;
    auto layout = ResizableSplitLeft(features, textarea, &size);

    auto component = Renderer(layout, [&] {
        return vbox({
            text("Top"),
            separator(),
            layout->Render() | flex,
            })| border;
    }) ;

    auto do_nothing = [&] {};

    // Instanciate the main and modal components:
    auto modal_component = DialogComponent(filePath, do_nothing, hide_modal);

    component |= Modal(modal_component, &modal_shown);

    screen.Loop(component);

}