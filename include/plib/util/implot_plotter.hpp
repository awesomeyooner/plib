#ifndef PLOTTER_HPP
#define PLOTTER_HPP

#include <iostream>
#include <cstdio>

#include "plib/util/system.hpp"
#include "plib/util/status.hpp"
#include "plib/util/logger.hpp"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "implot/implot.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>


/**
 * @brief Plotter class using ImPlot as the backend
 * 
 */
class Plotter{

    public:

        /**
         * @brief Initialize ImGui and its backends
         * 
         * @param window_name `std::string` Default "My Window" - The name of the window to use
         * @param verbose `bool` Flag for displaying error output 
         * @return `status_utils::StatusCode` OK if successful, FAILED otherwise 
         */
        static status_utils::StatusCode initialize(std::string window_name = "My Window", bool verbose = false);


        // static status_utils::StatusCode update()
    private:

        // The number of points to have in a window
        static int m_resolution;

        // SDL Window
        static SDL_Window* window;

        // OpenGL Context
        static SDL_GLContext gl_context;

}; // class Plotter

// The code below is from `implot_demo.cpp`, this code is not mine

namespace ImGui{

// utility structure for realtime plot
struct ScrollingBuffer {
    int MaxSize;
    int Offset;
    ImVector<ImVec2> Data;
    ScrollingBuffer(int max_size = 2000) {
        MaxSize = max_size;
        Offset  = 0;
        Data.reserve(MaxSize);
    }
    void AddPoint(float x, float y) {
        if (Data.size() < MaxSize)
            Data.push_back(ImVec2(x,y));
        else {
            Data[Offset] = ImVec2(x,y);
            Offset =  (Offset + 1) % MaxSize;
        }
    }
    void Erase() {
        if (Data.size() > 0) {
            Data.shrink(0);
            Offset  = 0;
        }
    }
};
    
// utility structure for realtime plot
struct RollingBuffer {
    float Span;
    ImVector<ImVec2> Data;
    RollingBuffer() {
        Span = 10.0f;
        Data.reserve(2000);
    }
    void AddPoint(float x, float y) {
        float xmod = fmodf(x, Span);
        if (!Data.empty() && xmod < Data.back().x)
            Data.shrink(0);
        Data.push_back(ImVec2(xmod, y));
    }
};

} // namespace ImGui


#endif // PLOTTER_HPP