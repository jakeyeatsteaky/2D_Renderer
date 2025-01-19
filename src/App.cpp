#include "SDL2/SDL.h"
#include "glad.h"
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

App::App() : m_initialized(false),
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
    if (0 != m_sdl->initCode)
    {
        ERR("Could Not initialize SDL", SDL_GetError());
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    m_windowObj = std::make_unique<Window>();
    bool initParam1 = m_windowObj->Init();

    SDL_GLContext glContext = SDL_GL_CreateContext(m_windowObj->GetWindow());
    if (!glContext)
    {
        ERR("Failed to create SDL GL Context: %s", SDL_GetError());
        return;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        ERR("Failed to initialize GLAD");
        return;
    }

    glViewport(0, 0, util::WINDOW_HEIGHT, util::WINDOW_WIDTH);

    LOG("Renderer: %s", glGetString(GL_RENDERER));
    LOG("OpenGL version supported: ", glGetString(GL_VERSION));

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

    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    const char *fragShaderSource = "#version 330 core\n"
                                   "out vec4 fragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\0";

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

    SDL_GL_SwapWindow(m_windowObj->GetWindow());
}

void App::Run()
{
    if (!m_initialized)
    {
        LOG("Failed to initialize the application");
        throw std::runtime_error("RUN failed");
    }

    while (!AppShouldQuit())
    {

        Input();
        Update();
        Render();
    }
}
