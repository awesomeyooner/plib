cmake_minimum_required(VERSION 3.12)

project( plib LANGUAGES CXX )

# === Main Library ===
add_library(plib
    src/util/logger.cpp
    src/util/status.cpp
    src/util/gnu_plotter.cpp
    src/util/util.cpp

    src/i2c/i2c.cpp
    src/i2c/wire_device.cpp

    # ImGUI
    lib/imgui/imgui_demo.cpp
    lib/imgui/imgui_draw.cpp
    lib/imgui/imgui_tables.cpp
    lib/imgui/imgui_widgets.cpp
    lib/imgui/imgui.cpp

    # ImPlot
    lib/implot/implot_demo.cpp
    lib/implot/implot_items.cpp
    lib/implot/implot.cpp

)

target_include_directories(plib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(plib PUBLIC cxx_std_17)

add_executable(Test test/test.cpp)
target_link_libraries(Test PRIVATE plib)