#include <memory>  // for shared_ptr, allocator, __shared_ptr_access
#include <string>

#include "ftxui/component/component.hpp"  // for Renderer, ResizableSplitBottom, ResizableSplitLeft, ResizableSplitRight, ResizableSplitTop
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for Element, operator|, text, center, border

#include "MainWindow.h"

using namespace ftxui;

std::function<void()> handleMenuClick(MainWindow &win)
// возможно содание такой функции ошибка
{
    return [&]
    {
        win.key = win.itemsWindow[win.selected_tab].keyFilter; // нужно чтобы обновлялась строка input при переходе на новую закладку

    };
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

    auto input_key = Input(&key, "key entry field", {.on_change = filterOwner(key)});

    auto buttonExport = Button("Export", showModal(modal_shown));

    auto containerButton = Container::Vertical({
                                                   input_key,
                                                   buttonExport,
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
                    });
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
    auto tab_toggle = HMenu(&tab_titles, &selected_tab, *this);

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
std::function<void()> MainWindow::filterOwner(std::string &key)
{
    // так как мы знаем selected_tab очень удобно управлять обьектами
    return [&]
    {
        itemsWindow[selected_tab].keyFilter = key; // для сохранения значения фильтра

        itemsWindow[selected_tab].containerLog->DetachAllChildren();

        if (key.empty()) //оставил условие, как мне кажется оно добавляет читабельность
        {
            for (auto &it : itemsWindow[selected_tab].getBufferLogs()) {
                itemsWindow[selected_tab].appendLogToWindow(it);
            }
        }
        else
        {
            for (auto &it : itemsWindow[selected_tab].getBufferLogs()) {
                if (key.compare(it.owner) == 0) {
                    itemsWindow[selected_tab].appendLogToWindow(it);
                }
            }
        }
    };
}