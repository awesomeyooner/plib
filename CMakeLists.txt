cmake_minimum_required(VERSION 3.12)

project( plib LANGUAGES CXX )

add_library(plib
    src/util/logger.cpp
    src/util/status.cpp
    src/util/gnu_plotter.cpp
    src/util/util.cpp
)

target_include_directories(plib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(plib PUBLIC cxx_std_20)

add_executable(Test test/test.cpp)
target_link_libraries(Test PRIVATE plib)