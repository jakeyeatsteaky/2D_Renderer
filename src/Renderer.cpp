#include <fstream>
#include <filesystem>

#include "Renderer.hpp"
#include "Utility.hpp"
#include "App.hpp"
#include "Shader.hpp"

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

std::vector<std::string> vertSource{};
std::vector<std::string> fragSource{};
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
    // find shader directory
    // parse shader, create shader object, add to vec of shaders

    // create shader program will happen elsewhere

    vertSource = get_shader_source(util::SHADER_SOURCE_DIR_VERT);
    fragSource = get_shader_source(util::SHADER_SOURCE_DIR_FRAG);
    
    if (fragSource.size() != vertSource.size()) LOG("Some shaders do not have a paired matching.");

    size_t numShaders = std::less(vertSource.size(), fragSource.size());

    for (size_t i = 0 ; i < numShaders; i++) {
        Shader shader;
        if (0 = shader.construct(vertSource[i].c_str(), fragSource[i].c_str()))  
            m_shaders.push_back(shader);
    }
}

void Renderer::render()
{
    //load_shaders();
    // const char *vertexShaderSource = "#version 330 core\n"
    //                                  "layout (location = 0) in vec3 aPos;\n"
    //                                  "void main()\n"
    //                                  "{\n"
    //                                  "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    //                                  "}\0";

    const char* vertShaderSource = vertSource[0].c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertShaderSource, NULL);
    glCompileShader(vertexShader);

    // const char *fragShaderSource = "#version 330 core\n"
    //                                "out vec4 fragColor;\n"
    //                                "void main()\n"
    //                                "{\n"
    //                                "   fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    //                                "}\0";

    const char* fragShaderSource = fragSource[0].c_str();

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragShaderSource, NULL);
    glCompileShader(fragmentShader);

// checking error for shader compilation:
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

// checking error for shader program linked correctly:
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
}; 

    // Vertex Buffer Objects
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glClearColor(0.4f, 0.3f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    SDL_GL_SwapWindow(getSDLWindow());
}

