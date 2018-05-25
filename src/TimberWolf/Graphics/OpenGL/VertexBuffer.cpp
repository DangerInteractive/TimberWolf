#include "../../../../include/TimberWolf/Graphics/OpenGL/VertexBuffer.hpp"

/**
 * @class tw::VertexBuffer
 *
 * Handle representing an OpenGL VBO (vertex buffer object).
 */

/**
 * Default constructor. Creates a VBO on the graphics card.
 */
tw::VertexBuffer::VertexBuffer () {

    glGenBuffers(1, &m_id);

}

/**
 * Constructor taking in an ID to an existing VBO. This should only be used to
 * create a handle to a VBO created manually.
 *
 * @param id VBO ID
 */
tw::VertexBuffer::VertexBuffer (GLuint id)
: m_id(id) {}

/**
 * Destructor. Deletes VBO on the graphics card if it is not in use.
 */
tw::VertexBuffer::~VertexBuffer () {

    glDeleteBuffers(1, &m_id);

}

/**
 * Get the ID of the VBO on the graphics card.
 *
 * @return VBO ID
 */
GLuint tw::VertexBuffer::getId () const {

    return m_id;

}

/**
 * Bind the VBO (make it the currently selected VBO).
 */
void tw::VertexBuffer::bind () {

    glBindBuffer(GL_ARRAY_BUFFER, m_id);

}

/**
 * Unbind the currently bound VBO (bind null VBO).
 */
void tw::VertexBuffer::unbind () {

    glBindBuffer(GL_ARRAY_BUFFER, 0);

}
