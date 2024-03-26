//
// Created by dika on 11.03.2024.
//

#include "TabController.hpp"

TabController::TabController()
{
    bufferLogs.set_capacity(sizeCapacity);
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
