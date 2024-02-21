//
// Created by dika on 15.02.2024.
//

#include"../include/MyCollapsible.hpp"

Component MyCollapsible(ConstStringRef label, Ref<bool> show) {
    class Impl : public ComponentBase {
    public:
        Impl(ConstStringRef label, Ref<bool> show) : show_(show) {
            CheckboxOption opt;
            opt.transform = [](EntryState s) {            // NOLINT
                auto prefix = text(s.state ? "▼ " : "▶ ");  // NOLINT
                auto t = paragraph(s.state ? s.label : "<...>");
                if (s.active) {
                    t |= bold;
                }
                if (s.focused) {
                    t |= inverted;
                }
                return hbox({prefix, t});
            };
            Add(Container::Vertical({
                                            Checkbox(label, show_.operator->(), opt),
                                    }));
        }
        Ref<bool> show_;
    };

    return Make<Impl>(std::move(label), show);
}