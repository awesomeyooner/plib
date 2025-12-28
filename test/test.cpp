#include <iostream>
#include <cstdio>

#include "plib/util/util.hpp"
#include "plib/util/system.hpp"
#include "plib/util/implot_plotter.hpp"

#include "plib/i2c/i2c.hpp"
#include "plib/i2c/wire_device.hpp"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "implot/implot.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

void display_plot();

int main()
{
    // // Initialize SDL
    // if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    // {
    //     std::printf("Error: %s\n", SDL_GetError());
    //     return -1;
    // }

    // // OpenGL Settings
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    // SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    // SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    // // Create Initial Window
    // SDL_Window* window = SDL_CreateWindow(
    //     "My Window",
    //     SDL_WINDOWPOS_CENTERED,
    //     SDL_WINDOWPOS_CENTERED,
    //     800, 600,
    //     SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    // );

    // // Create Context
    // SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    // SDL_GL_MakeCurrent(window, gl_context);
    // SDL_GL_SetSwapInterval(1); // vsync

    // // Initialize ImGui
    // IMGUI_CHECKVERSION();
    // ImGui::CreateContext();
    // ImPlot::CreateContext();
    // ImGui::StyleColorsDark();

    // // Initialize SDL2 and OpenGL for ImGui
    // ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    // ImGui_ImplOpenGL3_Init("#version 330");

    // // Keep alive
    // bool running = true;
    
    // ImGui::ScrollingBuffer data;
    // float history = 10;
    // ImPlotAxisFlags flags = ImPlotAxisFlags_AutoFit; //ImPlotAxisFlags_NoTickLabels;

    // while (running)
    // {
    //     SDL_Event event;
    //     while (SDL_PollEvent(&event))
    //     {
    //         ImGui_ImplSDL2_ProcessEvent(&event);
    //         if (event.type == SDL_QUIT)
    //             running = false;
    //     }

    //     ImGui_ImplOpenGL3_NewFrame();
    //     ImGui_ImplSDL2_NewFrame();
    //     ImGui::NewFrame();

    //     ImGui::Begin("Hello");
    //     ImGui::Text("ImGui + SDL2 + OpenGL works!");

    //     ImGui::SliderFloat("History", &history, 1, 30, "%.3f s");

    //     data.AddPoint(System::get_time_since_start(), sin(System::get_time_since_start()));

    //     if(ImPlot::BeginPlot("My Plot"))
    //     {
    //         ImPlot::SetupAxes("Time (s)", "Y Axis", flags, flags);
    //         ImPlot::SetupAxisLimits(ImAxis_X1, System::get_time_since_start() - history, System::get_time_since_start(), ImGuiCond_Always);
    //         // ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 1);
    //         ImPlot::PlotLine("My Line Plot", &data.Data[0].x, &data.Data[0].y, data.Data.size(), 0, data.Offset, 2*sizeof(float));
    //         ImPlot::EndPlot();
    //     }


    //     ImGui::End();

    //     ImGui::Render();

    //     glViewport(0, 0, 800, 600);
    //     glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    //     glClear(GL_COLOR_BUFFER_BIT);

    //     ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    //     SDL_GL_SwapWindow(window);
    // }

    // // Cleanup
    // ImGui_ImplOpenGL3_Shutdown();
    // ImGui_ImplSDL2_Shutdown();
    // ImGui::DestroyContext();
    // ImPlot::DestroyContext();

    // SDL_GL_DeleteContext(gl_context);
    // SDL_DestroyWindow(window);
    // SDL_Quit();
    display_plot();

    return 0;
}

void display_plot()
{
    ImPlotter::initialize();

    while(System::is_alive())
    {
        ImPlotter::push_data(sin(System::get_time_since_start()));

        if(ImPlotter::update() == status_utils::StatusCode::FAILED)
            System::shutdown();
    }

    ImPlotter::shutdown();
}