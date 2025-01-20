#ifndef WINDOWING_HPP
#define WINDOWING_HPP

#include "SDL2/SDL.h"
#include <memory>

class Window
{
private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;

public:
    Window();
    ~Window() noexcept;
    bool Init();
    SDL_Window* GetSDLWindow();

};
#endif //end windowing hpp