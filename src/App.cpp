#include "SDL2/SDL.h"
#include "App.hpp"
#include "Logger.hpp"
#include "Utility.hpp"


SDLInit::SDLInit()
{
    initCode = SDL_Init(SDL_INIT_VIDEO);
}

SDLInit::~SDLInit()
{
    LOG("\tDestroying the SDL Instance");
    SDL_Quit();
}

App::App() :
    m_initialized(false),
    m_isRunning(false),
    m_windowObj(nullptr),
    m_events(nullptr)
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
    if(0 != m_sdl->initCode) {
        ERR("Could Not initialize SDL", SDL_GetError());
        return;
    }

    m_windowObj = std::make_unique<Window>();
    bool initParam1 = m_windowObj->Init();

    m_events = std::make_unique<EventManager>();
    bool initParam2 = m_events->Init();

    m_initialized = initParam1 && initParam2;
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

}

void App::Run()
{
    if(!m_initialized) {
        LOG("Failed to initialize the application");
        throw std::runtime_error("RUN failed");
    }

    int count = 10;
    while(!AppShouldQuit() && count > 0) {

        Input();
        Update();
        Render();

        util::TimeDelay_ms(1000);
        count--;
        LOG("iteration:", count);
    }


}
