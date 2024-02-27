cmake_minimum_required (VERSION 3.11)
 
project(log_monitor LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
 GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
 GIT_TAG main # Important: Specify a version or a commit hash here.
)

FetchContent_Declare(ftxui-grid-container
        GIT_REPOSITORY https://github.com/mingsheng13/grid-container-ftxui
        GIT_TAG master
)

FetchContent_MakeAvailable(ftxui)
FetchContent_MakeAvailable(ftxui-grid-container)

add_library(DialogComponent
        Model/DialogComponent/src/DialogComponent.cpp
        Model/DialogComponent/include/DialogComponent.hpp
)
add_library(MainWindow
        Model/MainWindow/src/MainWindow.cpp
        Model/MainWindow/include/MainWindow.h
)
add_library(MyCollapsible
        Model/MyCollapsible/src/MyCollapsible.cpp
        Model/MyCollapsible/include/MyCollapsible.hpp
)

#set_target_properties(DialogComponent PROPERTIES PUBLIC_HEADER Model/DialogComponent/include/DialogComponent.hpp)
#set_target_properties(MainWindow PROPERTIES PUBLIC_HEADER Model/MainWindow/include/MainWindow.h)
#set_target_properties(MyCollapsible PROPERTIES PUBLIC_HEADER Model/MyCollapsible/include/MyCollapsible.hpp)


target_include_directories(DialogComponent PRIVATE Model/DialogComponent/include)
target_include_directories(MainWindow PRIVATE Model/MainWindow/include)
target_include_directories(MyCollapsible PRIVATE Model/MyCollapsible/include)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(MainWindow
        PUBLIC DialogComponent
)

target_link_libraries(MyCollapsible
        PUBLIC ftxui::screen
        PUBLIC ftxui::dom
        PUBLIC ftxui::component
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE ftxui-grid-container
        PRIVATE MainWindow
        PRIVATE MyCollapsible
)

