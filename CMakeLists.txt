cmake_minimum_required(VERSION 3.12)

project( plib LANGUAGES C CXX )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

# === Main Library ===
add_library(plib
    src/util/logger.cpp
    src/util/status.cpp
    src/util/gnu_plotter.cpp
    src/util/util.cpp
    src/util/system.cpp

    src/i2c/drivers/psd17.cpp

    src/math/motion/cubic_hermite_spline.cpp
    src/math/control/pid_controller.cpp
)

target_include_directories(plib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib>
        $<INSTALL_INTERFACE:lib>
        # $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/backends>
        # $<INSTALL_INTERFACE:lib/imgui/backends>
        # $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/implot>
        # $<INSTALL_INTERFACE:lib/implot>
)

target_compile_features(plib PUBLIC cxx_std_17)

# Add the test executables only if this project is at the top level (aka not used with add_subdirectory)
if(PROJECT_IS_TOP_LEVEL)
    add_executable(Test test/test.cpp)
    target_link_libraries(Test PRIVATE 
        plib 
    )
endif()