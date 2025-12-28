#include "plib/util/implot_plotter.hpp"


status_utils::StatusCode Plotter::initialize(std::string window_name, bool verbose)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        // If verbose is enabled, log the error
        if(verbose)
            Logger::error(std::string("Plotter::initialize - ") + SDL_GetError());

        return status_utils::StatusCode::FAILED;
    }

    // OpenGL Settings
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    // Create the window
    window = SDL_CreateWindow(
        window_name.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600, // Width, Height
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    // Create Context
    gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // vsync

    // Initialize ImGui
    if(verbose)
        IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGui::StyleColorsDark();

    // Initialize SDL2 and OpenGL for ImGui
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 330");

} // end of "initialize"


int Plotter::m_resolution = 100;
SDL_Window* Plotter::window = nullptr;
SDL_GLContext Plotter::gl_context = NULL;