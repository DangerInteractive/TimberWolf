#include "../include/VertexBuffer.hpp"

tw::VertexBuffer::VertexBuffer () {

    glGenBuffers(1, &m_id);

}

tw::VertexBuffer::VertexBuffer (GLuint id)
: m_id(id) {}

tw::VertexBuffer::~VertexBuffer () {

    glDeleteBuffers(1, &m_id);

}

GLuint tw::VertexBuffer::getId () const {

    return m_id;

}

GLint tw::VertexBuffer::getVertexSize () const {

    return m_vertexSize;

}

GLenum tw::VertexBuffer::getDataType () const {

    return m_dataType;

}

GLboolean tw::VertexBuffer::isNormalized () const {

    return m_normalized;

}

GLsizei tw::VertexBuffer::getVertexStride () const {

    return m_vertexStride;

}

void tw::VertexBuffer::write (const std::vector<GLvoid*>& data, GLint size, GLenum type, GLboolean normalized, GLsizei stride) {

    m_vertexSize = size;
    m_dataType = type;
    m_normalized = normalized;
    m_vertexStride = stride;

    bind();
    glBufferData(GL_ARRAY_BUFFER, data.size(), &data.front(), GL_STATIC_DRAW);
    unbind();

}

void tw::VertexBuffer::bind () {

    glBindBuffer(GL_ARRAY_BUFFER, m_id);

}

void tw::VertexBuffer::unbind () {

    glBindBuffer(GL_ARRAY_BUFFER, 0);

}
