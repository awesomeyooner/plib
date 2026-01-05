#include <iostream>
#include <cstdio>

#include "plib/util/util.hpp"
#include "plib/util/system.hpp"
#include "plib/util/implot_plotter.hpp"

#include "plib/math/motion/cubic_hermite_spline.hpp"
#include "plib/math/motion/my_class.hpp"

#include "plib/i2c/i2c.hpp"
#include "plib/i2c/wire_device.hpp"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "implot/implot.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>



void test_plotter()
{
    // Initialize Plotter
    ImPlotter::initialize();

    // Loop until user requests to quit
    while (System::is_alive())
    {
        // Sample Data
        ImPlotter::push_data(sin(System::get_time_since_start()), "My First Line Plot");
        ImPlotter::push_data(cos(System::get_time_since_start()), "My Second Line Plot");

        // If the user requests to quit, then shutdown
        if (ImPlotter::update() == status_utils::StatusCode::FAILED)
            System::shutdown();
    }

    // Shutdown Plotter
    ImPlotter::shutdown();

} // end of "test_plotter"


void test_spline()
{
    ImPlotter::initialize();

    // CubicHermiteSpline spline;

    // double bob = spline.k;

    while (System::is_alive())
    {
        std::function<status_utils::StatusCode(SDL_Window*, SDL_GLContext&)> runnable;

        runnable = 
            [](SDL_Window* window, SDL_GLContext& context){

                double P0, v0, P1, v1, ka, kv, k;

                ImGui::InputDouble("P0", &P0);

                if(ImPlot::BeginPlot("My Plot", ImVec2(-1, -1)))
                {
                    
                    ImPlot::SetupAxes("X Axis", "Y Axis", ImPlotAxisFlags_PanStretch, ImPlotAxisFlags_PanStretch);
                    // ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 1);

                    std::vector<double> data_x = {1, 2, 3, 4};
                    std::vector<double> data_y = {1, 2, 3, 4};

                    ImPlot::PlotLine("My Plot", data_x.data(), data_y.data(), data_x.size());
                        
                    ImPlot::EndPlot();
                }

                return status_utils::StatusCode::OK;
            };

        if ( ImPlotter::plot_custom(runnable) == status_utils::StatusCode::FAILED )
            System::shutdown();
    }

    ImPlotter::shutdown();

} // end of "test_spline"


int main()
{
    // test_spline();

    Logger::info(MyClass::my_function());

    return 0;
} // end of "main"