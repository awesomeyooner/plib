#include <iostream>
#include <cstdio>
#include <type_traits>

#include "plib/util/util.hpp"
#include "plib/util/system.hpp"
#include "plib/util/implot_plotter.hpp"

#include "plib/math/motion/cubic_hermite_spline.hpp"

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

    CubicHermiteSpline spline;

    double* P0 = &spline.m_P0;
    double* v0 = &spline.m_v0;
    double* P1 = &spline.m_P1;
    double* v1 = &spline.m_v1;

    double* a_max = &spline.m_a_max;
    double* v_max = &spline.m_v_max;

    double slider_min = -50;
    double slider_max = 50;

    int resolution = 1000;

    while (System::is_alive())
    {
        std::function<status_utils::StatusCode(SDL_Window*, SDL_GLContext&)> runnable;

        runnable = 
            [&spline, P0, v0, P1, v1, a_max, v_max, slider_min, slider_max, &resolution](SDL_Window* window, SDL_GLContext& context){

                ImGui::InputDouble("P0 Input", P0);
                ImGui::SliderScalar("P0 Slider", ImGuiDataType_Double, P0, &slider_min, & slider_max, "%.1f Units");

                ImGui::InputDouble("v0 Input", v0);
                ImGui::SliderScalar("v0 Slider", ImGuiDataType_Double, v0, &slider_min, & slider_max, "%.1f Units");

                ImGui::InputDouble("P1 Input", P1);
                ImGui::SliderScalar("P1 Slider", ImGuiDataType_Double, P1, &slider_min, & slider_max, "%.1f Units");

                ImGui::InputDouble("v1 Input", v1);
                ImGui::SliderScalar("v1 Slider", ImGuiDataType_Double, v1, &slider_min, & slider_max, "%.1f Units");

                ImGui::InputDouble("a_max Input", a_max);
                ImGui::SliderScalar("a_max Slider", ImGuiDataType_Double, a_max, &slider_min, & slider_max, "%.1f Units");

                ImGui::InputDouble("v_max Input", v_max);
                ImGui::SliderScalar("v_max Slider", ImGuiDataType_Double, v_max, &slider_min, & slider_max, "%.1f Units");

                ImGui::SliderInt("Resolution", &resolution, 100, 5000, "%d Units");

                double ka = spline.get_ka();
                double kv = spline.get_kv();
                double k = spline.get_k();
                double total_time = spline.get_total_time();

                std::string ka_text = "ka: " + std::to_string(ka);
                std::string kv_text = "kv: " + std::to_string(kv);
                std::string k_text = "k: " + std::to_string(k);
                std::string total_time_text = "Total Time: " + std::to_string(total_time);
                
                ImGui::Text(ka_text.c_str());
                ImGui::Text(kv_text.c_str());
                ImGui::Text(k_text.c_str());
                ImGui::Text(total_time_text.c_str());

                if(ImPlot::BeginPlot("My Plot", ImVec2(-1, -1)))
                {
                    
                    ImPlot::SetupAxes("X Axis", "Y Axis", ImPlotAxisFlags_PanStretch, ImPlotAxisFlags_PanStretch);
                    // ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 1);

                    std::vector<double> data_x;
                    std::vector<double> data_y;

                    for (size_t i = 0; i < resolution; i++)
                    {
                        double time = ( (double)i / (double)resolution ) * spline.get_total_time();
                        double output = spline.P(time);

                        data_x.push_back(time);
                        data_y.push_back(output);

                    }

                    Logger::debug(data_x.at(resolution - 1));
                    Logger::debug(data_y.at(resolution - 1));

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
    test_spline();

    return 0;

} // end of "main"