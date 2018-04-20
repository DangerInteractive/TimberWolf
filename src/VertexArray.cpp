#include "../include/VertexArray.hpp"

tw::VertexArray::VertexArray () {

    glGenVertexArrays(1, &m_id);

}

tw::VertexArray::VertexArray (GLuint id)
: m_id(id) {}

tw::VertexArray::~VertexArray () {

    glDeleteVertexArrays(1, &m_id);

}

void tw::VertexArray::bind () {

    glBindVertexArray(m_id);

}

void tw::VertexArray::unbind () {

    glBindVertexArray(0);

}
