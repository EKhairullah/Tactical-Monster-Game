cmake_minimum_required(VERSION 3.5)
project(Sample VERSION 0.1 LANGUAGES CXX)

# Qt settings
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)

# Find Qt packages
# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# List all source files (update paths if needed)
file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h")
file(GLOB UI_FILES ".ui")
file(GLOB RESOURCES "*.qrc")

# Create executable
add_executable(Sample
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
    ${RESOURCES}
    agentpage.ui
    secondpage.ui
    propreties.ui
)
set(PROJECT_SOURCES
        main.cpp
        agentpage.cpp agentpage.h agentpage.ui
        propreties.cpp propreties.h propreties.ui
        secondpage.cpp secondpage.h secondpage.ui
    )
# Link Qt
target_link_libraries(Sample PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Sample PRIVATE MainBoard)
