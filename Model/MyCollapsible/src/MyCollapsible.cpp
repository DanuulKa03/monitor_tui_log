//
// Created by dika on 15.02.2024.
//

#include"MyCollapsible.hpp"
#include "../../Json/include/json.hpp"

Component MyCollapsible(const LogItem& item, Component child, Ref<bool> show) {
    class Impl : public ComponentBase {
    public:
        Impl(const LogItem& item, Component child, Ref<bool> show) : show_(show) {
            CheckboxOption opt;
            opt.transform = [item](const EntryState& s) {
                auto prefix = text(s.state ? "▼ " : "▶ ");
                auto date_time = text(item.date_time);
                auto firmware = text(item.firmware) | bold;
                auto owner = text(item.owner);

                if (item.firmware == "Warning") {
                    firmware |= color(Color::Yellow1);
                    prefix |= color(Color::Yellow1);
                } else if (item.firmware == "Critical" || item.firmware == "Fatal") {
                    firmware |= color(Color::Red);
                    prefix |= color(Color::Red);
                }

                auto threeDots = paragraph(s.state ? s.label : "{...}");

                return hbox({prefix, text(" "), date_time, text(" "), firmware, text(" "),
                             owner, text(": "), threeDots});
            };
            Add(Container::Vertical({
                                            Checkbox(item.payload, show_.operator->(), opt),
                                            Maybe(std::move(child), show_.operator->()),
            }));
        }
        Ref<bool> show_;
    };

    return Make<Impl>(std::move(item), std::move(child), show);
}

Component MyCollapsible(const LogItem &item, Ref<bool> show) {
    class Impl : public ComponentBase {
    public:
        Impl(const LogItem& item, Ref<bool> show) : show_(show) {
            CheckboxOption opt;
            opt.transform = [item](const EntryState& s) {
                auto prefix = text(s.state ? "▼ " : "▶ ");
                auto date_time = text(item.date_time);
                auto firmware = text(item.firmware) | bold;
                auto owner = text(item.owner);

                if (item.firmware == "Warning") {
                    firmware |= color(Color::Yellow);
                    prefix |= color(Color::Yellow);
                } else if (item.firmware == "Critical" || item.firmware == "Fatal") {
                    firmware |= color(Color::Red);
                    prefix |= color(Color::Red);
                }

                auto threeDots = paragraph(s.state ? s.label : "{...}");

                return hbox({prefix, text(" "), date_time, text(" "), firmware, text(" "),
                             owner, text(": "), threeDots});
            };
            Add(Container::Vertical({
                                            Checkbox(item.payload, show_.operator->(), opt),
                                    }));
        }
        Ref<bool> show_;
    };

    return Make<Impl>(std::move(item), show);
}
