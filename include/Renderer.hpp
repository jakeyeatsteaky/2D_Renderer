#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <vector>
#include <SDL2/SDL.h>
#include "glad.h"

#include "Shader.hpp"
#include "VertexArray.hpp"

class App;
class Shader;

class Renderer
{
public:
    Renderer(const App &app);
    ~Renderer();
    bool Init();
    void render();

private:
    const App &m_app;
    SDL_Window *getSDLWindow();
    std::vector<Shader> m_shaderPrograms;
    std::vector<VAO> m_vertexArrays;

    void load_shaders();
    std::vector<std::string> get_shader_source(const char *path);
    unsigned int GetActiveShaderProgram();
};

#endif // RENDERER_HPP
