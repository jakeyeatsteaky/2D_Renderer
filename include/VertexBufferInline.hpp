
template <typename T>
VBO::VBO(T* data, size_t size, bool ebo, int drawType)
 {
    
    m_bufferType = (ebo) ? GL_ELEMENT_ARRAY_BUFFER : GL_ARRAY_BUFFER;
    GLenum usage = (drawType == 0) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;

    glGenBuffers(1, &m_vboID);
    glBindBuffer(m_bufferType, m_vboID);
    glBufferData(m_bufferType, size, data, usage);

}