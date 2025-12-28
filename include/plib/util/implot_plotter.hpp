#ifndef IMPLOT_PLOTTER_HPP
#define IMPLOT_PLOTTER_HPP

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

/**
 * @brief Plotter class using ImPlot as the backend
 * 
 */
class ImPlotter{

    public:

        /**
         * @brief Initialize ImGui and its backends
         * 
         * @param window_name `std::string` Default "My Window" - The name of the window to use
         * @param verbose `bool` Flag for displaying error output 
         * @return `status_utils::StatusCode` OK if successful, FAILED otherwise 
         */
        static status_utils::StatusCode initialize(std::string window_name = "My Window", bool verbose = false);


        /**
         * @brief Display the plot
         * 
         * @return `status_utils::StatusCode` FAILED if exit request sent. OK otherwise 
         */
        static status_utils::StatusCode update();


        /**
         * @brief Push new data to the buffer
         * 
         * @param x_data `double` The X Axis value. Typically Time
         * @param y_data `double` The Y Axis value. Your actual data 
         */
        static void push_data(double x_data, double y_data);


        /**
         * @brief Push new data to the buffer with time automatically filled in
         * 
         * @param data `double` The data to plot
         */
        static void push_data(double data);

        /**
         * @brief Shutdown ImGui and the backends
         * 
         */
        static void shutdown(); 

    private:

        // SDL Window
        static SDL_Window* m_window;

        // OpenGL Context
        static SDL_GLContext m_gl_context;

        // History / Width of Plot
        static float m_history;

        // Data Buffer
        static ImGui::ScrollingBuffer m_data;

        // Flags
        static ImPlotAxisFlags m_axis_flags;

}; // class ImPlotter




#endif // IMPLOT_PLOTTER_HPP