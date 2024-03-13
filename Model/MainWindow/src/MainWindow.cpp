#include <memory>  // for shared_ptr, allocator, __shared_ptr_access
#include <string>

#include "ftxui/component/component.hpp"  // for Renderer, ResizableSplitBottom, ResizableSplitLeft, ResizableSplitRight, ResizableSplitTop
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for Element, operator|, text, center, border
#include "ftxui/screen/color.hpp"

#include "MainWindow.h"

using namespace ftxui;

Component HMenu1(std::vector<std::string> *entries, int *selected)
{
    return Menu(entries, selected,
                {
        .on_change =
                });
}

MainWindow::MainWindow(size_t countTabulations)
    : title_("Monitor log")
{
    for (size_t i = 0; i < countTabulations; i++) {
        tab_titles.push_back("Tab " + std::to_string(i + 1));
        itemsWindow.push_back(TabController());
    }
}

void MainWindow::Run()
{

    auto screen = ScreenInteractive::Fullscreen();

    // Instanciate the main and modal components:
    bool modal_shown = false; //отображается ли окно или нет
    std::string filePath; //путь до файла, который передается через диалоговое окно
    auto modal_component = DialogComponent(filePath, exportFile(), hideModal(modal_shown));

    std::string key;
    auto input_key = Input(&key, "key entry field",
                           {
                               //это обработка ввода текста
                               .on_change = itemsWindow[selected_tab].filterOwner(key),
                           });

    auto buttonExport = Button("Export", showModal(modal_shown));
    auto buttonAdd = Button("Add",
                            [&]
                            {

                            });
    auto containerButton = Container::Vertical({
                                                   input_key,
                                                   buttonExport,
                                                   buttonAdd
                                               });
    auto leftContainer = Renderer(containerButton, [&]
    {
        return vbox({

                        hbox({
                                 text("key : "),
                                 input_key->Render()
                             }),

                        separator(),
                        buttonExport->Render(),
                        buttonAdd->Render(),
                    }) | flex_grow;
    });

    // for Test
    auto bla1 = Renderer(itemsWindow[0].containerLog, [&]
    { return hflow({itemsWindow[0].containerLog->Render() | vscroll_indicator | yframe | xflex,}); });
    auto bla2 = Renderer(itemsWindow[1].containerLog, [&]
    { return hflow({itemsWindow[1].containerLog->Render() | vscroll_indicator | yframe | xflex,}); });
    auto bla3 = Renderer(itemsWindow[2].containerLog, [&]
    { return hflow({itemsWindow[2].containerLog->Render() | vscroll_indicator | yframe | xflex,}); });

    auto tab = Container::Tab(
        {
            bla1,
            bla2,
            bla3,
        },
        &selected_tab);

    int size = 30;
    auto tab_toggle = HMenu1(&tab_titles, &selected_tab);

    auto layout = ResizableSplitLeft(leftContainer, tab, &size);

    auto containerMain = Container::Vertical({
                                                 tab_toggle,
                                                 layout,
                                             });

    //TODO !!! Сделать нормальное разбиение на функции по примеру menu_style.cpp

    auto component = Renderer(containerMain, [&]
    {
        return vbox({
                        tab_toggle->Render(),
                        separator(),
                        layout->Render() | flex,
                    }) | border;
    });

    component |= Modal(modal_component, &modal_shown);

    screen.Loop(component);

}

// Это обработчкик событий сохранения файла
std::function<void()> MainWindow::exportFile()
{
    return [&]
    {

    };
}
std::function<void()> MainWindow::showModal(bool &modal_shown)
{
    return [&]
    {
        modal_shown = true;
    };
}
std::function<void()> MainWindow::hideModal(bool &modal_shown)
{
    return [&]
    {
        modal_shown = false;
    };
}
std::function<void()> MainWindow::handleMenuClick()
{
    return [&]
    {

    };
}
