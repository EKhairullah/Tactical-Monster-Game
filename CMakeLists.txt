cmake_minimum_required(VERSION 3.16)

project(MainBoard VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# منابع پروژه، بدون main.cpp
set(MAINBOARD_SOURCES
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    hexagoncontroller.cpp
    hexagoncontroller.h
    hexagonground.h
    chooseground.cpp
    chooseground.h
    chooseground.ui
    resource.qrc
    
)


add_library(MainBoard STATIC
    ${MAINBOARD_SOURCES}
    mainboard_luncher.h mainboard_luncher.cpp
    
    resource.qrc
)


target_link_libraries(MainBoard PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)

target_include_directories(MainBoard PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
