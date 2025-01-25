#include "VertexBuffer.hpp"

#include <SDL2/SDL.h>
#include "glad.h"

template <typename T>
VBO::VBO(T* data, size_t size) 
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

unsigned int VBO::GetGPUId()
{
    return m_vboID;
}