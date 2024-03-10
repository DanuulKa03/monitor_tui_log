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
        Model/JsonParser/src/getJson.cpp
        Model/LogValidator/src/LogValidator.cpp
)
add_library(JsonParser
        Model/JsonParser/src/getJson.cpp
        Model/JsonParser/include/getJson.hpp
)
target_include_directories(log_monitor PRIVATE "Model/MainWindow/include")
target_include_directories(log_monitor PRIVATE "Model/LogValidator/include")
target_include_directories(log_monitor PRIVATE "Model/JsonParser/include")

target_link_libraries(log_monitor
 PRIVATE ftxui::screen
 PRIVATE ftxui::dom
 PRIVATE ftxui::component # Not needed for this example.
)

