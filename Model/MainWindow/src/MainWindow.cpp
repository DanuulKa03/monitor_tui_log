#include <memory>  // for shared_ptr, allocator, __shared_ptr_access
#include <string>

#include "ftxui/component/component.hpp"  // for Renderer, ResizableSplitBottom, ResizableSplitLeft, ResizableSplitRight, ResizableSplitTop
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for Element, operator|, text, center, border
#include "ftxui/screen/color.hpp"

#include "MainWindow.h"

#include <nlohmann/json.hpp>
using JSON = nlohmann::json;

using namespace ftxui;

Component
Inner(std::vector<Component> children)
{
    Component vlist = Container::Vertical(std::move(children));
    return Renderer(vlist, [vlist]
    {
        return hbox({
                        text(" "),
                        vlist->Render(),
                    });
    });
}

MainWindow::MainWindow()
    : title_("Monitor log")
{
    bufferLogs.set_capacity(sizeCapacity);
}

void
MainWindow::Run()
{

    auto screen = ScreenInteractive::Fullscreen();

    bool modal_shown = false;
    std::string filePath; //путь до файла, который передается через диалоговое окно

    // Some actions modifying the state:
    auto show_modal = [&]
    { modal_shown = true; };
    auto hide_modal = [&]
    { modal_shown = false; };

    std::string key;
    auto input_key = Input(&key, "key entry field",
                           {
                               //это обработка ввода текста
                               .on_change = [&]
                               {

                                   containerLog->DetachAllChildren();

                                   for (auto &it : bufferLogs) {
                                       if (key.compare(it.owner) == 0) {
                                           appendLogToWindow(it);
                                       }

                                   }

                               },
                           });

    auto buttonExport = Button("Export", show_modal);

    // for Test
    containerLog = Container::Vertical({});

    auto textarea = Renderer(containerLog, [&]
    {
        return hflow({
                         containerLog->Render() | vscroll_indicator | yframe,
                     });
    });
    auto buttonAdd = Button("Add",
                            [&]
                            {
                                LogItem log1("[2024-02-05 18:36:54]",
                                             "Debug",
                                             "Mqtt",
                                             "Published message of size 178 to topic customer/1/dev/394/v70");
                                LogItem log2("[2024-02-05 18:36:54]",
                                             "Critical",
                                             "Mqtt",
                                             "Published message of size 178 to topic customer/1/dev/394/v70",
                                             {
                                                 {"Adviser::onTelemetryUpdated(const QString&) const@adviser.cpp:248",
                                                  PayloadType::code}
                                             });
                                LogItem log3("[2024-02-05 18:36:54]", "Warning", "Mqtt", "Message to enqueue",
                                             {
                                                 {"{\"course\":\"0\",\"gps_quality\":\"1.46\",\"gps_time\":\"183651\",\"hdop\":\"1.46\",\"height\":\"112.1\",\"lat\":\"51.310804\",\"lon\":\"40.504654\",\"satelite_count\":\"8\",\"speed\":\"1.029712\",\"time\":\"1707158212622\",\"x_acceleration\":\"0\",\"x_vibration_amplitude\":\"0\",\"x_vibration_frequency\":\"0\",\"x_vibration_speed\":\"0\",\"y_acceleration\":\"0\",\"y_vibration_amplitude\":\"0\",\"y_vibration_speed\":\"0\",\"z_acceleration\":\"0\",\"z_vibration_amplitude\":\"0\",\"z_vibration_frequency\":\"0\",\"z_vibration_speed\":\"0\"}",
                                                  PayloadType::json},
                                                 {"size: 460, schema_id: 70", PayloadType::text}
                                             });

                                this->bufferLogs.push_back(std::move(log1));
                                this->bufferLogs.push_back(std::move(log2));
                                this->bufferLogs.push_back(std::move(log3));

                                appendLogToWindow(bufferLogs[0]);
                                appendLogToWindow(bufferLogs[1]);
                                appendLogToWindow(bufferLogs[2]);

                            });

    auto containerButton = Container::Vertical({
                                                   input_key,
                                                   buttonExport,
                                                   buttonAdd
                                               });

    auto features = Renderer(containerButton, [&]
    {
        return vbox({

                        hbox({
                                 text("key : "),
                                 input_key->Render()
                             }),

                        separator(),
                        buttonExport->Render(),
                        buttonAdd->Render(),
                    });
    });

    int size = 30;
    auto layout = ResizableSplitLeft(features, textarea, &size);

    auto component = Renderer(layout, [&]
    {
        return vbox({
                        text("Top"),
                        separator(),
                        layout->Render() | flex,
                    }) | border;
    });

    auto do_nothing = [&]
    {};

    // Instanciate the main and modal components:
    auto modal_component = DialogComponent(filePath, do_nothing, hide_modal);

    component |= Modal(modal_component, &modal_shown);

    screen.Loop(component);

}

bool
MainWindow::appendLogToWindow(LogItem &item)
{
    std::vector<Component> children;
    for (auto &it : item.payloadVector) {

        switch (it.second) {
            case PayloadType::text:

                children.push_back(Renderer([it]
                                            {
                    return paragraph(it.first);
                                            }));

                break;
            case PayloadType::json: {
                JSON json;
                if (ParseJSON(it.first, json)) {
                    Expander expander = ExpanderImpl::Root();
                    auto json_test = From(json, /*is_last=*/true, /*depth=*/0, expander);

                    // Wrap it inside a frame, to allow scrolling.
                    json_test =
                        Renderer(json_test, [json_test]
                        { return json_test->Render() | yframe; });

                    children.push_back(json_test);
                }
                else {
                    // TODO нужно сделать обрабтку ошибок
                }

                break;
            }
            case PayloadType::code:

                children.push_back(Renderer([it]
                                            { return text(it.first) | bgcolor(Color::Yellow); }));

                break;
        }
    }

    if (!children.empty()) {
        this->containerLog->Add(MyCollapsible(item, Inner(children)));

    }
    else {
        this->containerLog->Add(MyCollapsible(item));
    }


    return false;
}