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

int main()
{
    // ImPlotter::initialize();

    while (System::is_alive())
    {
        ImPlotter::push_data(sin(System::get_time_since_start()), "My First Line Plot");
        ImPlotter::push_data(cos(System::get_time_since_start()), "My Second Line Plot");

        if (ImPlotter::update() == status_utils::StatusCode::FAILED)
            System::shutdown();
    }

    ImPlotter::shutdown();

    return 0;
}