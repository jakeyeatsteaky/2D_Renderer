#ifndef APP_HPP
#define APP_HPP

#include <memory>
#include "Windowing.hpp"
#include "EventManager.hpp"

class SDLInit
{
public:
    SDLInit();
    ~SDLInit();

    int initCode;
};

class App
{
private:
    bool m_initialized;
    bool m_isRunning;
    std::unique_ptr<SDLInit> m_sdl;
    std::unique_ptr<Window> m_windowObj;
    std::unique_ptr<EventManager> m_events;

    void Setup();
    bool AppShouldQuit();

    void Input();
    void Update();
    void Render();

public:
    App();
    ~App() noexcept;

    void Run();
};

#endif // APP_HPP
