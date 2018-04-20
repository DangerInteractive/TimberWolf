#include "../include/VertexBuffer.hpp"

tw::VertexBuffer::VertexBuffer () {

    glGenBuffers(1, &m_id);

}

tw::VertexBuffer::VertexBuffer (GLuint id)
: m_id(id) {}

tw::VertexBuffer::~VertexBuffer () {

    glDeleteBuffers(1, &m_id);

}

void tw::VertexBuffer::bind () {

    glBindBuffer(GL_ARRAY_BUFFER, m_id);

}

void tw::VertexBuffer::unbind () {

    glBindBuffer(GL_ARRAY_BUFFER, 0);

}
