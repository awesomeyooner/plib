#include "plib/util/implot_plotter.hpp"


status_utils::StatusCode ImPlotter::initialize(std::string window_name, bool verbose)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        // If verbose is enabled, log the error
        if(verbose)
            Logger::error(std::string("ImPlotter::initialize - ") + SDL_GetError());

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
    m_window = SDL_CreateWindow(
        window_name.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600, // Width, Height
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    // Create Context
    m_gl_context = SDL_GL_CreateContext(m_window);
    SDL_GL_MakeCurrent(m_window, m_gl_context);
    SDL_GL_SetSwapInterval(1); // vsync

    // Initialize ImGui
    if(verbose)
        IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGui::StyleColorsDark();

    // Initialize SDL2 and OpenGL for ImGui
    ImGui_ImplSDL2_InitForOpenGL(m_window, m_gl_context);
    ImGui_ImplOpenGL3_Init("#version 330");

} // end of "initialize"


status_utils::StatusCode ImPlotter::update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);

        if (event.type == SDL_QUIT)
            return status_utils::StatusCode::FAILED;
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Hello");
    ImGui::Text("ImGui + SDL2 + OpenGL works!");

    ImGui::SliderFloat("History", &m_history, 1, 30, "%.1f s");

    if(ImPlot::BeginPlot("My Plot"))
    {
        ImPlot::SetupAxes("Time (s)", "Y Axis", m_axis_flags, m_axis_flags);
        ImPlot::SetupAxisLimits(ImAxis_X1, System::get_time_since_start() - m_history, System::get_time_since_start(), ImGuiCond_Always);
        // ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 1);
        ImPlot::PlotLine("My Line Plot", &m_data.Data[0].x, &m_data.Data[0].y, m_data.Data.size(), 0, m_data.Offset, 2*sizeof(float));
        ImPlot::EndPlot();
    }

    ImGui::End();

    ImGui::Render();

    glViewport(0, 0, 800, 600);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(m_window);

    return status_utils::StatusCode::OK;

} // end of "update"


void ImPlotter::push_data(double x_data, double y_data)
{
    // Append the data point to the buffer
    m_data.AddPoint(x_data, y_data);

} // end of "push_data"


void ImPlotter::push_data(double data)
{
    // Fill in X Axis value as time since start
    push_data(System::get_time_since_start(), data);
    
} // end of "push_data"


void ImPlotter::shutdown()
{
    // Cleanup everything
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    ImPlot::DestroyContext();

    SDL_GL_DeleteContext(m_gl_context);
    SDL_DestroyWindow(m_window);
    SDL_Quit();

} // end of "shutdown"


SDL_Window* ImPlotter::m_window = nullptr;
SDL_GLContext ImPlotter::m_gl_context = NULL;

float ImPlotter::m_history = 10;
ImGui::ScrollingBuffer ImPlotter::m_data;
ImPlotAxisFlags ImPlotter::m_axis_flags = ImPlotAxisFlags_AutoFit;