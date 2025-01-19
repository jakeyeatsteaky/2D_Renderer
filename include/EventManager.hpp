#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <SDL2/SDL.h>

class EventManager
{
private:
    bool m_shouldQuit;

public:
    EventManager();
    ~EventManager() noexcept;

    bool Init();
    void Poll();

    bool quitEvent();
    void handleKeyDown(SDL_KeyboardEvent);
};

#endif //end event manager hpp