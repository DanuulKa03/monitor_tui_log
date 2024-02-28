#include <memory>  // for shared_ptr, allocator, __shared_ptr_access
#include <string>

#include "ftxui/component/component.hpp"  // for Renderer, ResizableSplitBottom, ResizableSplitLeft, ResizableSplitRight, ResizableSplitTop
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for Element, operator|, text, center, border
#include "ftxui/screen/color.hpp"
#include "MainWindow.h"
#include "../../DialogComponent/include/DialogComponent.hpp"
#include "../../MyCollapsible/include/MyCollapsible.hpp"
#include "../../Json/include/json.hpp"

#include <nlohmann/json.hpp>
using JSON = nlohmann::json;

using namespace ftxui;

MainWindow::MainWindow() : title_("Monitor log") {}

Component Inner(std::vector<Component> children) {
    Component vlist = Container::Vertical(std::move(children));
    return Renderer(vlist, [vlist] {
        return hbox({
                            text(" "),
                            vlist->Render(),
                    });
    });
}

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
        return hflow({
                            container->Render() | vscroll_indicator | yframe,
                    });
    });
    auto buttonAdd = Button("Add", [&]{
        std::string jsonString = "{\"course\":\"0\",\"gps_quality\":\"2.08\",\"gps_time\":\"183648\",\"hdop\":\"2.08\",\"height\":\"111.8\",\"lat\":\"51.310811\",\"lon\":\"40.504652\",\"satelite_count\":\"6\",\"speed\":\"0.859328\",\"time\":\"1707158209623\",\"x_acceleration\":\"0\",\"x_vibration_amplitude\":\"0\",\"x_vibration_frequency\":\"0\",\"x_vibration_speed\":\"0\",\"y_acceleration\":\"0\",\"y_vibration_amplitude\":\"0\",\"y_vibration_speed\":\"0\",\"z_acceleration\":\"0\",\"z_vibration_amplitude\":\"0\",\"z_vibration_frequency\":\"0\",\"z_vibration_speed\":\"0\"}";
        JSON json;
        ParseJSON(jsonString,json);
        Expander expander = ExpanderImpl::Root();
        auto json_test = From(json, /*is_last=*/true, /*depth=*/0, expander);

        // Wrap it inside a frame, to allow scrolling.
        json_test =
                Renderer(json_test, [json_test] { return json_test->Render() | yframe; });

        Event previous_event;
        Event next_event;
        auto wrapped_component = CatchEvent(json_test, [&](Event event) {
            previous_event = next_event;
            next_event = event;

            // 'G' and 'gg -------------------------------------------------------------
            if (event == Event::Character('G')) {
                while (json_test->OnEvent(Event::ArrowUp))
                    ;
                return true;
            }
            if (previous_event == Event::Character('g') &&
                next_event == Event::Character('g')) {
                while (json_test->OnEvent(Event::ArrowDown))
                    ;
                return true;
            }

            // Allow the user to quit using 'q' or ESC ---------------------------------
            if (event == Event::Character('q') || event == Event::Escape) {
                screen.ExitLoopClosure()();
                return true;
            }

            // Convert mouse whell into their corresponding Down/Up events.-------------
            if (!event.is_mouse())
                return false;
            if (event.mouse().button == Mouse::WheelDown) {
                screen.PostEvent(Event::ArrowDown);
                return true;
            }
            if (event.mouse().button == Mouse::WheelUp) {
                screen.PostEvent(Event::ArrowUp);
                return true;
            }
            return false;
        });
        container->Add(MyCollapsible("Feb 05 18:36:49 imx8 PiklemaLauncher[83418]: [2024-02-05 18:36:49] "
                                     "(Firmware:Info) Controller: ",
                                     Inner({
                                         json_test,
                                     })
                                     )
        );
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