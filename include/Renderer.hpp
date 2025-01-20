#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <vector>

#include "Shader.hpp"
#include "SDL2/SDL.h"
#include "glad.h"

class App;
class Shader;

class Renderer {
public:
    Renderer(const App& app);
    ~Renderer();
    bool Init();

    void render();
    void load_shaders();

private:
    const App& m_app;
    SDL_Window* getSDLWindow();
    std::vector<Shader> m_vertShaders;
    std::vector<Shader> m_fragShaders;
};

#endif // RENDERER_HPP
