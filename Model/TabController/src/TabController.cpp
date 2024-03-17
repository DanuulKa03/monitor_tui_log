//
// Created by dika on 11.03.2024.
//

#include "TabController.hpp"

TabController::TabController()
{
    bufferLogs.set_capacity(sizeCapacity);

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

}

bool TabController::appendLogToWindow(LogItem &item)
{
    std::vector<ftxui::Component> children;
    for (auto &it : item.payloadVector) {

        switch (it.second) {
            case PayloadType::text:

                children.push_back(Renderer([it]
                                            {
                                                return ftxui::paragraph(it.first);
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
                        { return json_test->Render() | ftxui::yframe; });

                    children.push_back(json_test);
                }
                else {
                    // TODO нужно сделать обрабтку ошибок
                }

                break;
            }
            case PayloadType::code:

                children.push_back(Renderer([it]
                                            { return ftxui::text(it.first) | ftxui::bgcolor(ftxui::Color::Yellow); }));

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
Component TabController::Inner(std::vector<Component> children)
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
boost::circular_buffer<LogItem> &TabController::getBufferLogs()
{
    return bufferLogs;
}
