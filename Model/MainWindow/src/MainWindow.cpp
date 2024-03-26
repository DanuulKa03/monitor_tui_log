#include <string>

#include "ftxui/component/component.hpp"  // for Renderer, ResizableSplitBottom, ResizableSplitLeft, ResizableSplitRight, ResizableSplitTop
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for Element, operator|, text, center, border

#include "MainWindow.h"

using namespace ftxui;

std::function<void()> handleMenuClick(MainWindow &win)
// возможно создание такой функции ошибка
{
    return [&]
    {
        win.key = win.itemsWindow[win.selected_tab].keyFilter; // нужно чтобы обновлялась строка input при переходе на новую закладку

    };
}

MainWindow::MainWindow(size_t countTabulations_)
    : title_("Monitor log"), countTabulations(countTabulations_)
{
    for (size_t i = 0; i < countTabulations; i++) {
        tab_titles.push_back("Tab " + std::to_string(i + 1));
        itemsWindow.emplace_back();
    }
}

void MainWindow::Run()
{

    auto screen = ScreenInteractive::Fullscreen();

    // Instance the main and modal components:
    bool modal_shown = false; //отображается ли окно или нет
    std::string filePath; //путь до файла, который передается через диалоговое окно
    auto modal_component = DialogComponent(filePath, exportFile(), hideModal(modal_shown));

    auto input_key = Input(&key, "key entry field", {.on_change = filterOwner()});

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

    //добавление в tab обьектов, для отображения
    auto tab = Container::Tab( {},&selected_tab );
    for (size_t i = 0; i < countTabulations; i++) {
        tab->Add( Renderer(itemsWindow[i].containerLog, [i, this]
        { return hflow({itemsWindow[i].containerLog->Render() | vscroll_indicator | yframe | xflex,}); }) );
    }

    int size = 30; //размер окна по умолчанию, который может меня окно
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

// Это обработчик событий сохранения файла
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
std::function<void()> MainWindow::filterOwner()
{
    // так как мы знаем selected_tab очень удобно управлять объектами
    return [&]
    {
        itemsWindow[selected_tab].keyFilter = this->key; // для сохранения значения фильтра

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
                if (this->key == it.owner) {
                    itemsWindow[selected_tab].appendLogToWindow(it);
                }
            }
        }
    };
}