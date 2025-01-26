#include "VertexArray.hpp"
#include "glad.h"

VAO::VAO() : initialized(false)
{
    glGenVertexArrays(1, &m_vaoID);
}

void VAO::add_vbo(VBO &&vbo)
{
    m_vertexBuffers.push_back(std::move(vbo));
}

void VAO::init_vbo()
{
    glBindVertexArray(m_vaoID);

    for (const auto &vbo : m_vertexBuffers)
    {
        vbo.activate();
    }

    // unbind current because binding the vertex array is done in a separate call: make_active
    glEnableVertexAttribArray(0);

    initialized = true;
}

void VAO::make_active()
{
    glEnableVertexAttribArray(m_vaoID);
}

unsigned int VAO::getVAOId()
{
    return (unsigned int)m_vaoID;
}