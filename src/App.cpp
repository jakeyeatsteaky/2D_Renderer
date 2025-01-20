#include "App.hpp"
#include "Utility.hpp"

constexpr int SDL_GL_MAJ_VER = 3;
constexpr int SDL_GL_MIN_VER = 3;

SDLInit::SDLInit()
{
    initCode = SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, SDL_GL_MAJ_VER);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, SDL_GL_MIN_VER);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}

SDLInit::~SDLInit()
{
    LOG("\tDestroying the SDL Instance");
    SDL_Quit();
}

App::App() : m_initialized(false),
             m_isRunning(false),
             m_windowObj(nullptr),
             m_events(nullptr),
             m_renderer(nullptr)
{
    Setup();
}

App::~App() noexcept
{
    LOG("Destroying the App:");
}

void App::Setup()
{
    m_sdl = std::make_unique<SDLInit>();
    if (0 != m_sdl->initCode)
    {
        ERR("Could Not initialize SDL", SDL_GetError());
        return;
    }

    m_events = std::make_unique<EventManager>();
    bool initParam_event = m_events ? m_events->Init() : false;
    
    m_windowObj = std::make_unique<Window>();
    bool initParam_win = m_windowObj ? m_windowObj->Init() : false;

    m_renderer = std::make_unique<Renderer>(*this);
    bool initParam_rend = m_renderer ? m_renderer->Init() : false;  

    m_initialized = initParam_event & initParam_win & initParam_rend;
}

bool App::AppShouldQuit()
{
    return m_events->quitEvent();
}

void App::Input()
{
    m_events->Poll();
}

void App::Update()
{
}

void App::Render()
{
    m_renderer->render();   
}

void App::Run()
{
    if (!m_initialized)
    {
        LOG("Failed to initialize the application");
        throw std::runtime_error("RUN failed");
    }

    while (!AppShouldQuit())
    {

        Input();
        Update();
        Render();
    }
}
