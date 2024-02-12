cmake_minimum_required (VERSION 3.11)
 
project(log_monitor LANGUAGES CXX VERSION 1.0.0)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
 GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
 GIT_TAG main # Important: Specify a version or a commit hash here.
)
FetchContent_MakeAvailable(ftxui)

add_executable(log_monitor main.cpp Model/MainWindow/src/MainWindow.cpp
        Model/DialogComponent/src/DialogComponent.cpp
)

target_include_directories(log_monitor PRIVATE "Model/MainWindow/include")

target_link_libraries(log_monitor
 PRIVATE ftxui::screen
 PRIVATE ftxui::dom
 PRIVATE ftxui::component # Not needed for this example.
)

