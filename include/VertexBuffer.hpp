#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include <cstddef>
#include <vector>
#include "glad.h"

struct VBOMetaData
{
    VBOMetaData(GLuint loc, GLint size, GLenum type, GLboolean norm, GLsizei stride, GLuint offset);
    VBOMetaData() = delete;
    VBOMetaData(const VBOMetaData &copy) = delete;
    VBOMetaData(VBOMetaData &&move) = default;
    ~VBOMetaData() = default;

    void bind() const;

    GLuint location;      // index of the vertex attribute
    GLint size;           // number of components per vertex attrib (1,2,3 or 4)
    GLenum type;          // Data type of each component
    GLboolean normalized; // Should it be clamped to -1 to 1 (signed) 0 to 1 (unsigned)
    GLsizei stride;       // byte offset between components;
    GLint offset;         // offset of first components of first vertex attribute
};

class VBO
{
public:
    template <typename T>
    VBO(T *data, size_t size);
    VBO(VBO &&other) noexcept = default;
    VBO() = delete;
    VBO(const VBO &) = delete;
    ~VBO() = default;

    unsigned int GetGPUId();

    void AddAttribute(const unsigned location,
                      const int size,
                      const int type,
                      const bool normalized,
                      const size_t stride,
                      const int offset);

    void activate() const;

private:
    unsigned int m_vboID;
    std::vector<VBOMetaData> m_attribPointers;
};

#include "VertexBufferInline.hpp"

#endif // VERTEXBUFFER_HPP