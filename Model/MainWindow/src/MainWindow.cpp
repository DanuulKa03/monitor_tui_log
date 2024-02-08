#include "MainWindow.h"
#include <memory>  // for shared_ptr, allocator, __shared_ptr_access
 
#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Renderer, ResizableSplitBottom, ResizableSplitLeft, ResizableSplitRight, ResizableSplitTop
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for Element, operator|, text, center, border

using namespace ftxui;
MainWindow::MainWindow() : title_("My Application") {}

void MainWindow::Run() {
    auto left = Renderer([] { return text("Left") | center; });
    auto right = Renderer([] { return text("right") | center; });
    auto top = Renderer([] { return text("top") | center; });
/*
    int left_size = 20;
    int right_size = 20;
    int top_size = 10;
   */

    int left_right_size = 20;
    int top_size = 10;
    auto left_right = Renderer ([] {
        return hbox({
          left,
          right,
        });
    });

    auto container = Renderer([]{return text("");});
    container = ResizableSplitTop(top, container, &top_size);
   // container = ResizableSplitLeft(left, container, &left_size);
   // container = ResizableSplitRight(right, container, &right_size);
   


    auto renderer = Renderer(container, [&] { return container->Render() | border; });


    auto screen = ScreenInteractive::Fullscreen();
    screen.Loop(renderer);
}







void MainWindow::Render() {
   }

