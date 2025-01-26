
template <typename T>
VBO::VBO(T* data, size_t size) {
    
    glGenBuffers(1, &m_vboID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

}