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
        container->Add(Button("Feb 05 18:36:49 imx8 PiklemaLauncher[83418]: [2024-02-05 18:36:49] (Firmware:Info) Controller: Message to enqueue: {\"course\":\"0\",\"gps_quality\":\"2.08\",\"gps_time\":\"183648\",\"hdop\":\"2.08\",\"height\":\"111.8\",\"lat\":\"51.310811\",\"lon\":\"40.504652\",\"satelite_count\":\"6\",\"speed\":\"0.859328\",\"time\":\"1707158209623\",\"x_acceleration\":\"0\",\"x_vibration_amplitude\":\"0\",\"x_vibration_frequency\":\"0\",\"x_vibration_speed\":\"0\",\"y_acceleration\":\"0\",\"y_vibration_amplitude\":\"0\",\"y_vibration_speed\":\"0\",\"z_acceleration\":\"0\",\"z_vibration_amplitude\":\"0\",\"z_vibration_frequency\":\"0\",\"z_vibration_speed\":\"0\"}, size: 460, schema_id: 70", [&]{}, ButtonOption::Ascii()));
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