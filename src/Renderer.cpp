#include <fstream>
#include <filesystem>

#include "Renderer.hpp"
#include "Utility.hpp"
#include "App.hpp"
#include "Shader.hpp"
#include "VertexBuffer.hpp"

Renderer::Renderer(const App& app) : m_app(app) 
{

}

Renderer::~Renderer() 
{
    
}

SDL_Window* Renderer::getSDLWindow() 
{
    SDL_Window* window = nullptr;
    if (m_app.GetWindow()) {
        window = m_app.GetWindow()->GetSDLWindow();
    }

    return window;
}


bool Renderer::Init()
{
    SDL_Window* sdl_window = getSDLWindow();
    SDL_GLContext glContext = SDL_GL_CreateContext(sdl_window);
    if (!glContext) {
        ERR("Failed to create SDL GL Context: %s", SDL_GetError());
        return false;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        ERR("Failed to initialize GLAD");
        return false;
    }

    glViewport(0, 0, util::WINDOW_HEIGHT, util::WINDOW_WIDTH);

    LOG("Renderer: %s", glGetString(GL_RENDERER));
    LOG("OpenGL version supported: ", glGetString(GL_VERSION));

    load_shaders();
    load_vertex_data();

    return true;
}

namespace fs = std::filesystem;
std::vector<std::string> Renderer::get_shader_source(const char* path)
{
    std::vector<std::string> ret {};
    // need to get how many files are at this path
    fs::path cwd = fs::current_path();
    fs::path dir(path);
    if (fs::exists(dir)) {
        if (fs::is_directory(dir)) {
            fs::directory_iterator it(path);
            fs::directory_iterator end;
            
            for (; it != end; ++it) {
                std::fstream file(it->path());
                if (!file) {
                    ERR("Invalid Path: ", it->path());
                    continue;
                }
                std::string source;
                std::string line;
                while (std::getline(file, line)) {
                    source += line;
                    source += '\n';
                }
                source += '\0';
                ret.push_back(source.c_str());
                file.close();
            }
        } 
        else {
            ERR ("Path is not a directory: ", path);
        }
    } 
    else {
        ERR("File path does not exist: ", path);
    }

    return ret;
}

void Renderer::load_shaders()
{
    std::vector<std::string> vertSource = get_shader_source(util::SHADER_SOURCE_DIR_VERT);
    std::vector<std::string> fragSource = get_shader_source(util::SHADER_SOURCE_DIR_FRAG);
    
    if (fragSource.size() != vertSource.size()) LOG("Some shaders do not have a paired matching.");

    size_t numShaders = (vertSource.size() < fragSource.size()) ? vertSource.size() : fragSource.size();

    for (size_t i = 0 ; i < numShaders; i++) {
        Shader shader;
        if (shader.construct(vertSource[i].c_str(), fragSource[i].c_str()) > -1) {   
            m_shaderPrograms.push_back(std::move(shader));
        } 
    }

}

unsigned int VAO;
void Renderer::load_vertex_data()
{
   // !TODO: make Vertex object
   // have functino to import vertex data from disk (file)
   // store in renderer? m_vectorOfVertices. 
    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    }; 

// HEres how I want the flow
// 1 create a bunch of vbos and their metadata
// 2 make the vao
// 3 vao create state -> iterates through VBOs and does their OpenGL thing
// 4 add VAO to renderer
    VAO vao;
    vao.updateState()

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);


    VBO vbo(vertices, sizeof(vertices));
    
    glEnableVertexAttribArray(0);
}

unsigned int Renderer::GetActiveShaderProgram()
{
    return m_shaderPrograms[0]._id;
}

void Renderer::render()
{
    glClearColor(0.4f, 0.3f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(GetActiveShaderProgram());
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    SDL_GL_SwapWindow(getSDLWindow());
}

