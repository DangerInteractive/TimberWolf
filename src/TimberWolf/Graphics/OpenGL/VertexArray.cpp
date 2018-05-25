#include "../../../../include/TimberWolf/Graphics/OpenGL/VertexArray.hpp"

/**
 * @class tw::VertexArray
 *
 * Handle representing an OpenGL VAO (vertex array object).
 */

/**
 * Default constructor. Creates a VAO on the graphics card.
 */
tw::VertexArray::VertexArray () {

    glGenVertexArrays(1, &m_id);

}

/**
 * Constructor taking in an ID to an existing VAO. This should only be used to
 * create a handle to a VAO created manually.
 *
 * @param id VAO ID
 */
tw::VertexArray::VertexArray (GLuint id)
: m_id(id) {}

/**
 * Destructor. Deletes VAO on the graphics card if it is not in use.
 */
tw::VertexArray::~VertexArray () {

    glDeleteVertexArrays(1, &m_id);

}

/**
 * Get the ID of the VAO on the graphics card.
 *
 * @return VAO ID
 */
GLuint tw::VertexArray::getId () const {

    return m_id;

}

/**
 * Bind the VAO (make it the currently selected VAO).
 */
void tw::VertexArray::bind () {

    glBindVertexArray(m_id);

}

/**
 * Unbind the currently bound VAO (bind null VAO).
 */
void tw::VertexArray::unbind () {

    glBindVertexArray(0);

}
