cmake_minimum_required (VERSION 3.11)
 
project(log_monitor LANGUAGES CXX VERSION 1.0.0)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)

FetchContent_Declare(ftxui
 GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
 GIT_TAG main # Important: Specify a version or a commit hash here.
)

FetchContent_Declare(json
        URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz
)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

FetchContent_MakeAvailable(ftxui)

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

add_library(Json
        Model/Json/src/json.cpp
        Model/Json/include/json.hpp
        Model/Json/include/expander.hpp
        Model/Json/src/expander.cpp
        Model/Json/src/button.cpp
        Model/Json/include/button.hpp
        Model/Json/src/mytoggle.cpp
        Model/Json/include/mytoggle.hpp
)

#set_target_properties(DialogComponent PROPERTIES PUBLIC_HEADER Model/DialogComponent/include/DialogComponent.hpp)
#set_target_properties(MainWindow PROPERTIES PUBLIC_HEADER Model/MainWindow/include/MainWindow.h)
#set_target_properties(MyCollapsible PROPERTIES PUBLIC_HEADER Model/MyCollapsible/include/MyCollapsible.hpp)


target_include_directories(DialogComponent PRIVATE Model/DialogComponent/include)
target_include_directories(MainWindow PRIVATE Model/MainWindow/include)
target_include_directories(MyCollapsible PRIVATE Model/MyCollapsible/include)
target_include_directories(Json PRIVATE Model/Json/include)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(Json
        PUBLIC nlohmann_json::nlohmann_json
        PUBLIC ftxui::screen
        PUBLIC ftxui::dom
        PUBLIC ftxui::component
)

target_link_libraries(MainWindow
        PUBLIC nlohmann_json::nlohmann_json
        PUBLIC DialogComponent
)

target_link_libraries(MyCollapsible
        PRIVATE Json
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE MainWindow
        PRIVATE MyCollapsible
)