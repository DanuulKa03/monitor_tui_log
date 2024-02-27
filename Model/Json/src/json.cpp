//
// Created by dika on 27.02.2024.
//

#include "json.hpp"

bool ParseJSON(std::string input, JSON& out) {
    class JsonParser : public nlohmann::detail::json_sax_dom_parser<JSON> {
    public:
        JsonParser(JSON& j)
                : nlohmann::detail::json_sax_dom_parser<JSON>(j, false) {}
        bool parse_error(std::size_t /*position*/,
                         const std::string& /*last_token*/,
                         const JSON::exception& ex) {
            std::cerr << std::endl;
            std::cerr << ex.what() << std::endl;
            return false;
        }
    };
    JsonParser parser(out);
    return JSON::sax_parse(input, &parser);
}

Component FromString(const JSON& json, bool is_last) {
    std::string value = json;
    std::string str = "\"" + value + "\"";
    return Basic(str, Color::GreenLight, is_last);
}

Component FromNumber(const JSON& json, bool is_last) {
    return Basic(json.dump(), Color::CyanLight, is_last);
}

Component FromBoolean(const JSON& json, bool is_last) {
    bool value = json;
    std::string str = value ? "true" : "false";
    return Basic(str, Color::YellowLight, is_last);
}

Component FromNull(bool is_last) {
    return Basic("null", Color::RedLight, is_last);
}

Component Unimplemented() {
    return Renderer([] { return text("Unimplemented"); });
}

Component Empty() {
    return Renderer([] { return text(""); });
}

Component Basic(std::string value, Color c, bool is_last) {
    return Renderer([value, c, is_last](bool focused) {
        auto element = paragraph(value) | color(c);
        if (focused)
            element = element | inverted | focus;
        if (!is_last)
            element = hbox({element, text(",")});
        return element;
    });
}

Component From(const JSON& json, bool is_last, int depth, Expander& expander) {
    if (json.is_object())
        return FromObject(Empty(), json, is_last, depth, expander);
    if (json.is_array())
        return FromArrayAny(Empty(), json, is_last, depth, expander);
    if (json.is_string())
        return FromString(json, is_last);
    if (json.is_number())
        return FromNumber(json, is_last);
    if (json.is_boolean())
        return FromBoolean(json, is_last);
    if (json.is_null())
        return FromNull(is_last);
    return Unimplemented();
}

void DisplayMainUI(const JSON& json, bool fullscreen) {
    auto screen_fullscreen = ScreenInteractive::Fullscreen();
    auto screen_fit = ScreenInteractive::FitComponent();
    auto& screen = fullscreen ? screen_fullscreen : screen_fit;
    Expander expander = ExpanderImpl::Root();
    auto component = From(json, /*is_last=*/true, /*depth=*/0, expander);

    // Wrap it inside a frame, to allow scrolling.
    component =
            Renderer(component, [component] { return component->Render() | yframe; });

    Event previous_event;
    Event next_event;
    auto wrapped_component = CatchEvent(component, [&](Event event) {
        previous_event = next_event;
        next_event = event;

        // 'G' and 'gg -------------------------------------------------------------
        if (event == Event::Character('G')) {
            while (component->OnEvent(Event::ArrowUp))
                ;
            return true;
        }
        if (previous_event == Event::Character('g') &&
            next_event == Event::Character('g')) {
            while (component->OnEvent(Event::ArrowDown))
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

    screen.Loop(wrapped_component);
}
