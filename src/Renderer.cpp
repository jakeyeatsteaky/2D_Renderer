#include <fstream>
#include <filesystem>

#include "Renderer.hpp"
#include "Utility.hpp"
#include "App.hpp"
#include "Shader.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"

Renderer::Renderer(const App &app) : m_app(app)
{
}

Renderer::~Renderer()
{
}

SDL_Window *Renderer::getSDLWindow()
{
    SDL_Window *window = nullptr;
    if (m_app.GetWindow())
    {
        window = m_app.GetWindow()->GetSDLWindow();
    }

    return window;
}

bool Renderer::Init()
{
    SDL_Window *sdl_window = getSDLWindow();
    SDL_GLContext glContext = SDL_GL_CreateContext(sdl_window);
    if (!glContext)
    {
        ERR("Failed to create SDL GL Context: %s", SDL_GetError());
        return false;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        ERR("Failed to initialize GLAD");
        return false;
    }

    glViewport(0, 0, util::WINDOW_HEIGHT, util::WINDOW_WIDTH);

    LOG("Renderer: %s", glGetString(GL_RENDERER));
    LOG("OpenGL version supported: ", glGetString(GL_VERSION));

    load_shaders();
    load_vertex_data();

    unsigned idx = 0; // which VAOidx state to make active
    init_GL_state(idx);

    return true;
}

namespace fs = std::filesystem;
std::vector<std::string> Renderer::get_shader_source(const char *path)
{
    std::vector<std::string> ret{};
    // need to get how many files are at this path
    fs::path cwd = fs::current_path();
    fs::path dir(path);
    if (fs::exists(dir))
    {
        if (fs::is_directory(dir))
        {
            fs::directory_iterator it(path);
            fs::directory_iterator end;

            for (; it != end; ++it)
            {
                std::fstream file(it->path());
                if (!file)
                {
                    ERR("Invalid Path: ", it->path());
                    continue;
                }
                std::string source;
                std::string line;
                while (std::getline(file, line))
                {
                    source += line;
                    source += '\n';
                }
                source += '\0';
                ret.push_back(source.c_str());
                file.close();
            }
        }
        else
        {
            ERR("Path is not a directory: ", path);
        }
    }
    else
    {
        ERR("File path does not exist: ", path);
    }

    return ret;
}

void Renderer::load_shaders()
{
    std::vector<std::string> vertSource = get_shader_source(util::SHADER_SOURCE_DIR_VERT);
    std::vector<std::string> fragSource = get_shader_source(util::SHADER_SOURCE_DIR_FRAG);

    if (fragSource.size() != vertSource.size())
        LOG("Some shaders do not have a paired matching.");

    size_t numShaders = (vertSource.size() < fragSource.size()) ? vertSource.size() : fragSource.size();

    for (size_t i = 0; i < numShaders; i++)
    {
        Shader shader;
        if (shader.construct(vertSource[i].c_str(), fragSource[i].c_str()) > -1)
        {
            m_shaderPrograms.push_back(std::move(shader));
        }
    }
}

void Renderer::load_vertex_data()
{
    // !TODO: make Vertex object
    // have functino to import vertex data from disk (file)
    // store in renderer? m_vectorOfVertices.
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f};

    float vert[] = {
        -0.5f, 0.5f, 0.0f,
        -0.9f, 0.5f, 0.0f,
        -0.6f, 0.0f, 0.0f};

    // Create Vertex Array
    VAO vao; // glGenVertexArrays(1, &VAO);

    // Create Vertex Buffers which determine this VAO's state
    VBO vbo(vertices, sizeof(vertices));
    vbo.AddAttribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), 0);

    VBO vbo2(vert, sizeof(vert));
    vbo.AddAttribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), 0);

    // Add all VBOs to this VAO
    vao.add_vbo(std::move(vbo2));
    vao.add_vbo(std::move(vbo));

    m_vertexArrays.push_back(std::move(vao));
}

void Renderer::init_GL_state(unsigned vaoIdx)
{
    if (!m_vertexArrays[vaoIdx].initialized)
        m_vertexArrays[vaoIdx].init_vbo(); // glBindVertexArray(VAO); and then bind all vbos and attribs
    m_vertexArrays[vaoIdx].make_active();  // glEnableVertexAttribArray(thisVAOId);
    activeIdx = vaoIdx;
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
    glBindVertexArray(activeVAO());
    glDrawArrays(GL_TRIANGLES, 0, 6);

    SDL_GL_SwapWindow(getSDLWindow());
}
