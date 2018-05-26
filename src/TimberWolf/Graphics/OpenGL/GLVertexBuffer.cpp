#include "../../../../include/TimberWolf/Graphics/OpenGL/GLVertexBuffer.hpp"

/**
 * @class tw::GLVertexBuffer
 *
 * Handle representing an OpenGL VBO (vertex buffer object).
 */

/**
 * Default constructor. Creates a VBO on the graphics card.
 */
tw::GLVertexBuffer::GLVertexBuffer () {

    glGenBuffers(1, &m_id);

}

/**
 * Constructor taking in an ID to an existing VBO. This should only be used to
 * create a handle to a VBO created manually.
 *
 * @param id VBO ID
 */
tw::GLVertexBuffer::GLVertexBuffer (GLuint id)
: m_id(id) {}

/**
 * Destructor. Deletes VBO on the graphics card if it is not in use.
 */
tw::GLVertexBuffer::~GLVertexBuffer () {

    glDeleteBuffers(1, &m_id);

}

/**
 * Get the ID of the VBO on the graphics card.
 *
 * @return VBO ID
 */
GLuint tw::GLVertexBuffer::getId () const {

    return m_id;

}

/**
 * Bind the VBO (make it the currently selected VBO).
 */
void tw::GLVertexBuffer::bind () {

    glBindBuffer(GL_ARRAY_BUFFER, m_id);

}

/**
 * Unbind the currently bound VBO (bind null VBO).
 */
void tw::GLVertexBuffer::unbind () {

    glBindBuffer(GL_ARRAY_BUFFER, 0);

}
