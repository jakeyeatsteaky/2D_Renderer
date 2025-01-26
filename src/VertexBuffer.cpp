#include "VertexBuffer.hpp"

#include <SDL2/SDL.h>
#include "glad.h"

VBOMetaData::VBOMetaData(GLuint loc, GLint size, GLenum type, GLboolean norm, GLsizei stride, GLuint offset) : location(loc),
                                                                                                               size(size),
                                                                                                               type(type),
                                                                                                               normalized(norm),
                                                                                                               stride(stride),
                                                                                                               offset(offset)
{
}

void VBOMetaData::bind() const
{
    glVertexAttribPointer(location,
                          size,
                          type,
                          normalized,
                          stride,
                          reinterpret_cast<void *>(offset));
}

unsigned int VBO::GetGPUId()
{
    return m_vboID;
}

void VBO::AddAttribute(const unsigned location,
                       const int size,
                       const int type,
                       const bool normalized,
                       const size_t stride,
                       const int offset)
{
    VBOMetaData metaData((GLint)location,
                         (GLuint)size,
                         (GLenum)type,
                         (GLboolean)normalized,
                         (GLsizei)stride,
                         (GLint)offset);

    m_attribPointers.push_back(std::move(metaData));
}

void VBO::activate() const
{

    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
    for (const auto &attrib : m_attribPointers)
    {
        attrib.bind();
    }
}