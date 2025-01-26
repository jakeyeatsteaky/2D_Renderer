#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include "VertexBuffer.hpp"

class VAO {
public:
    VAO();
    ~VAO() = default;
    VAO(const VAO& copy) = delete;
    VAO(VAO&& move) = default;

    void add_vbo(VBO&& vbo);

    void init_vbo();
    void make_active();
    unsigned int getVAOId();

    bool initialized;

private:
    GLuint m_vaoID;
    std::vector<VBO> m_vertexBuffers;
};

#endif // VERTEXARRAY_HPP
