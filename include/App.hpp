#ifndef APP_HPP
#define APP_HPP

#include <memory>
#include "Windowing.hpp"
#include "EventManager.hpp"
#include "Renderer.hpp"

constexpr std::string SHADER_SOURCE_DIR_VERT = "/home/jakbak/2D_Renderer/shaders/vertex";
constexpr std::string SHADER_SOURCE_DIR_FRAG = "/home/jakbak/2D_Renderer/shaders/fragment";

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
    std::unique_ptr<Renderer> m_renderer;

    void Setup();
    bool AppShouldQuit();

    void Input();
    void Update();
    void Render();

public:
    App();
    App(const App&) = delete;
    App& operator=(const App&) = delete;
    ~App() noexcept;

    void Run();
    Window* GetWindow() const { return m_windowObj.get(); }

};

#endif // APP_HPP
