#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

class VAO {
public:
    VAO() = default;
    ~VAO() = default;
    VAO(const VAO& copy) = delete;
    VAO(VAO&& move) = default;


private:
    unsigned int m_vaoID;
};

#endif // VERTEXARRAY_HPP
