#include "EventManager.hpp"
#include "Logger.hpp"

EventManager::EventManager() :
    m_shouldQuit(false)
{
    LOG("Created Event Manager object");   
}

EventManager::~EventManager()
{
    LOG("\tDestroying EventManager object");
}

bool EventManager::Init()
{
    return true;
}

void EventManager::Poll()
{
    // Eventually can use the Observer pattern here for game events.  
    // system wide events just directly access the App object

    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type)
        {
            case SDL_QUIT:
                m_shouldQuit = true;
                break;
            case SDL_KEYDOWN:
                handleKeyDown(event.key);
            default:
                break;
        }
    }
}

bool EventManager::quitEvent()
{
    return m_shouldQuit;
}

void EventManager::handleKeyDown(SDL_KeyboardEvent e)
{
    SDL_Keycode code = e.keysym.sym;
    switch(code)
    {
        case SDLK_ESCAPE:
            m_shouldQuit = true;
            break;
        default:
            break;
    }
}