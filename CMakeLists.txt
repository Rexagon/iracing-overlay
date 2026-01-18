cmake_minimum_required(VERSION 3.31)
project(iracing_overlay)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick)

qt_standard_project_setup()

qt_add_executable(iracing_overlay
        src/main.cpp
        src/overlay_base.h
        src/overlay_base.cpp
        src/pedals_overlay.cpp
        src/pedals_overlay.h
        src/pedals_chart.cpp
        src/pedals_chart.h
)

target_include_directories(iracing_overlay PRIVATE src)

qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)
qt_add_qml_module(iracing_overlay
        URI Overlay
        VERSION 1.0
        QML_FILES
        ui/pedals.qml
        SOURCES
        src/pedals_chart.cpp
        src/pedals_chart.h
)

target_link_libraries(iracing_overlay PRIVATE Qt6::Core Qt6::Quick)

set_target_properties(iracing_overlay PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
)
