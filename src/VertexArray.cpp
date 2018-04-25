#include "../include/VertexArray.hpp"

tw::VertexArray::VertexArray () {

    glGenVertexArrays(1, &m_id);

}

tw::VertexArray::VertexArray (GLuint id)
: m_id(id) {}

tw::VertexArray::~VertexArray () {

    glDeleteVertexArrays(1, &m_id);

}

GLuint tw::VertexArray::getId () const {

    return m_id;

}

void tw::VertexArray::storeBuffer (GLuint index, VertexBuffer& vbo) {

    bind();
    vbo.bind();
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, vbo.getVertexSize(), vbo.getDataType(), vbo.isNormalized(), vbo.getVertexStride(), 0);
    vbo.unbind();
    unbind();

}

void tw::VertexArray::enableAttribute (GLuint index) {

    glEnableVertexAttribArray(index);

}

void tw::VertexArray::disableAttribute (GLuint index) {

    glDisableVertexAttribArray(index);

}

void tw::VertexArray::bind () {

    glBindVertexArray(m_id);

}

void tw::VertexArray::unbind () {

    glBindVertexArray(0);

}
