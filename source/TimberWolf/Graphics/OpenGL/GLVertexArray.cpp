#include "../../../../include/TimberWolf/Graphics/OpenGL/GLVertexArray.hpp"

/**
 * @class tw::GLVertexArray
 *
 * Handle representing an OpenGL VAO (vertex array object).
 */

/**
 * Default constructor. Creates a VAO on the graphics card.
 */
tw::GLVertexArray::GLVertexArray () {

    glGenVertexArrays(1, &m_id);

}

/**
 * Constructor taking in an ID to an existing VAO. This should only be used to
 * create a handle to a VAO created manually.
 *
 * @param id VAO ID
 */
tw::GLVertexArray::GLVertexArray (GLuint id)
: m_id(id) {}

/**
 * Destructor. Deletes VAO on the graphics card if it is not in use.
 */
tw::GLVertexArray::~GLVertexArray () {

    glDeleteVertexArrays(1, &m_id);

}

/**
 * Get the ID of the VAO on the graphics card.
 *
 * @return VAO ID
 */
GLuint tw::GLVertexArray::getId () const {

    return m_id;

}

/**
 * Bind the VAO (make it the currently selected VAO).
 */
void tw::GLVertexArray::bind () {

    glBindVertexArray(m_id);

}

/**
 * Unbind the currently bound VAO (bind null VAO).
 */
void tw::GLVertexArray::unbind () {

    glBindVertexArray(0);

}
