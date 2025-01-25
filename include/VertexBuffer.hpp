#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include <cstddef>

class VBO {
public:
    template <typename T>
    VBO(T* data, size_t size);
    VBO(VBO&& other) noexcept = default;
    VBO() = delete;
    VBO(const VBO&) = delete;
    ~VBO() = default;

    unsigned int GetGPUId();

private:
    unsigned int m_vboID;
};


#endif // VERTEXBUFFER_HPP