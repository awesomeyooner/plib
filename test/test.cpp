#include <iostream>
#include <cstdio>
#include <type_traits>

#include "plib/util/util.hpp"
#include "plib/util/system.hpp"
#include "plib/util/implot_plotter.hpp"

#include "plib/math/motion/cubic_hermite_spline.hpp"

#include "plib/math/control/pid_controller.hpp"

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
        ImPlotter::push_data(sin(System::get_epoch()), "My First Line Plot");
        ImPlotter::push_data(cos(System::get_epoch()), "My Second Line Plot");

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

    double* j_max = &spline.m_j_max;
    double* a_max = &spline.m_a_max;
    double* v_max = &spline.m_v_max;

    double slider_min = -50;
    double slider_max = 50;

    int resolution = 1000;

    while (System::is_alive())
    {
        std::function<status_utils::StatusCode(SDL_Window*, SDL_GLContext&)> runnable;

        runnable = 
            [&spline, P0, v0, P1, v1, j_max, a_max, v_max, slider_min, slider_max, &resolution](SDL_Window* window, SDL_GLContext& context){

                ImGui::InputDouble("P0 Input", P0);
                ImGui::SliderScalar("P0 Slider", ImGuiDataType_Double, P0, &slider_min, & slider_max, "%.1f Units");

                ImGui::InputDouble("v0 Input", v0);
                ImGui::SliderScalar("v0 Slider", ImGuiDataType_Double, v0, &slider_min, & slider_max, "%.1f Units");

                ImGui::InputDouble("P1 Input", P1);
                ImGui::SliderScalar("P1 Slider", ImGuiDataType_Double, P1, &slider_min, & slider_max, "%.1f Units");

                ImGui::InputDouble("v1 Input", v1);
                ImGui::SliderScalar("v1 Slider", ImGuiDataType_Double, v1, &slider_min, & slider_max, "%.1f Units");

                ImGui::InputDouble("j_max Input", j_max);
                ImGui::SliderScalar("j_max Slider", ImGuiDataType_Double, j_max, &slider_min, & slider_max, "%.1f Units");

                ImGui::InputDouble("a_max Input", a_max);
                ImGui::SliderScalar("a_max Slider", ImGuiDataType_Double, a_max, &slider_min, & slider_max, "%.1f Units");

                ImGui::InputDouble("v_max Input", v_max);
                ImGui::SliderScalar("v_max Slider", ImGuiDataType_Double, v_max, &slider_min, & slider_max, "%.1f Units");

                ImGui::SliderInt("Resolution", &resolution, 100, 5000, "%d Units");

                double kj = spline.get_kj();
                double ka = spline.get_ka();
                double kv = spline.get_kv();
                double k = spline.get_k();
                double total_time = spline.get_total_time();

                std::string kj_text = "kj: " + std::to_string(kj);
                std::string ka_text = "ka: " + std::to_string(ka);
                std::string kv_text = "kv: " + std::to_string(kv);
                std::string k_text = "k: " + std::to_string(k);
                std::string total_time_text = "Total Time: " + std::to_string(total_time);
                
                ImGui::Text(kj_text.c_str());
                ImGui::Text(ka_text.c_str());
                ImGui::Text(kv_text.c_str());
                ImGui::Text(k_text.c_str());
                ImGui::Text(total_time_text.c_str());

                if(ImPlot::BeginPlot("My Plot", ImVec2(-1, -1)))
                {
                    
                    ImPlot::SetupAxes("X Axis", "Y Axis", ImPlotAxisFlags_PanStretch, ImPlotAxisFlags_PanStretch);
                    // ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 1);

                    std::vector<double> data_x;
                    std::vector<double> P_data_y;
                    std::vector<double> P_prime_1_data_y;
                    std::vector<double> P_prime_2_data_y;
                    std::vector<double> P_prime_3_data_y;

                    for (size_t i = 0; i < resolution; i++)
                    {
                        double time = ( (double)i / (double)resolution ) * spline.get_total_time();
                        double P = spline.P(time);
                        double P_prime_1 = spline.P_prime_1(time);
                        double P_prime_2 = spline.P_prime_2(time);
                        double P_prime_3 = spline.P_prime_3(time);

                        data_x.push_back(time);
                        P_data_y.push_back(P);
                        P_prime_1_data_y.push_back(P_prime_1);
                        P_prime_2_data_y.push_back(P_prime_2);
                        P_prime_3_data_y.push_back(P_prime_3);

                    }

                    ImPlot::PlotLine("P(t)", data_x.data(), P_data_y.data(), data_x.size());
                    ImPlot::PlotLine("P'(t)", data_x.data(), P_prime_1_data_y.data(), data_x.size());
                    ImPlot::PlotLine("P''(t)", data_x.data(), P_prime_2_data_y.data(), data_x.size());
                    ImPlot::PlotLine("P'''(t)", data_x.data(), P_prime_3_data_y.data(), data_x.size());
                        
                    ImPlot::EndPlot();
                }

                return status_utils::StatusCode::OK;
            };

        if ( ImPlotter::plot_custom(runnable) == status_utils::StatusCode::FAILED )
            System::shutdown();
    }

    ImPlotter::shutdown();

} // end of "test_spline"


void test_pid()
{
    ImPlotter::initialize();

    PIDController pid_controller(0, 0, 0, 0, FeedForwardType::STATIC_SIGNED);

    while(System::is_alive())
    {
        pid_controller.m_integral_time_bound = M_PI;
        pid_controller.m_setpoint = 0;

        double time = System::get_epoch();

        double position = std::sin(time);

        pid_controller.calculate(time, position);

        // Negative since error is setpoint - position
        ImPlotter::push_data(-sin(time), "Error Reference");

        // Derivative of -sin(x) = -cos(x)
        ImPlotter::push_data(-cos(time), "Error Rate Reference");

        // Integral of -sin(x) from (x, x - pi) = cos(x) - cos(x - pi)
        ImPlotter::push_data(cos(time) - cos(time - M_PI), "Accumulated Error Reference");

        ImPlotter::push_data(pid_controller.get_error(), "Error");
        ImPlotter::push_data(pid_controller.get_error_rate(), "Error Rate");
        ImPlotter::push_data(pid_controller.get_accumulated_error(), "Accumulated Error");

        if ( ImPlotter::update() == status_utils::StatusCode::FAILED )
            System::shutdown();
    }

    ImPlotter::shutdown();
    
} // end of "test_pid"


void test_i2c()
{
    if (I2C::init_name("MCP2221", true) == status_utils::StatusCode::FAILED)
    {
        Logger::error("I2C Bus Failed to Initialize! Exiting...");
    }
} // end of "test_i2c"


int main()
{
    // test_spline();
    // test_pid();
    // test_plotter();
    // test_i2c();

    return 0;

} // end of "main"