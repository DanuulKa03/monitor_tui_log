cmake_minimum_required (VERSION 3.11)
 
project(log_monitor LANGUAGES CXX VERSION 1.0.0)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
set(BOOST_ENABLE_CMAKE ON)

FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG main # Important: Specify a version or a commit hash here.
)

#TODO разобаться с boost https://github.com/alandefreitas/FetchBoostContent/blob/develop/CMakeLists.txt
#TODO https://alandefreitas.github.io/FetchBoostContent/proposals/

FetchContent_Declare(Boost
        URL https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.xz
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
FetchContent_MakeAvailable(Boost)

add_library(DialogComponent
        Model/DialogComponent/src/DialogComponent.cpp
        Model/DialogComponent/include/DialogComponent.hpp
)

add_library(LogItem
        Model/LogItem/src/LogItem.cpp
        Model/LogItem/include/LogItem.hpp
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
        Model/Json/src/expander.cpp
        Model/Json/src/button.cpp
        Model/Json/src/mytoggle.cpp
        Model/Json/include/json.hpp
        Model/Json/include/expander.hpp
        Model/Json/include/button.hpp
        Model/Json/include/mytoggle.hpp
)

add_library(TabController
        Model/TabController/src/TabController.cpp
        Model/TabController/include/TabController.hpp
)

add_library(HMenu
        Model/HMenu/src/HMenu.cpp
        Model/HMenu/include/HMenu.hpp

)

target_include_directories(DialogComponent PRIVATE Model/DialogComponent/include)
target_include_directories(MainWindow PRIVATE Model/MainWindow/include)
target_include_directories(MyCollapsible PRIVATE Model/MyCollapsible/include)
target_include_directories(Json PRIVATE Model/Json/include)
target_include_directories(TabController PRIVATE Model/TabController/include)
target_include_directories(HMenu PRIVATE Model/HMenu/include)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(DialogComponent
        PUBLIC ftxui::dom
        PUBLIC ftxui::component
)

target_link_libraries(Json
        PUBLIC nlohmann_json::nlohmann_json
        PUBLIC ftxui::screen
        PUBLIC ftxui::dom
        PUBLIC ftxui::component
)

target_link_libraries(MainWindow
        PUBLIC nlohmann_json::nlohmann_json
        PUBLIC HMenu
        PUBLIC TabController
        PUBLIC DialogComponent
)

target_link_libraries(MyCollapsible
        PUBLIC Json
)

target_link_libraries(TabController
        PUBLIC Boost::circular_buffer
        PRIVATE ftxui::dom
        PRIVATE ftxui::component
        PRIVATE LogItem
        PRIVATE MyCollapsible
)

target_link_libraries(HMenu
        PUBLIC MainWindow
)

target_link_libraries(${PROJECT_NAME}
        PUBLIC MainWindow

)