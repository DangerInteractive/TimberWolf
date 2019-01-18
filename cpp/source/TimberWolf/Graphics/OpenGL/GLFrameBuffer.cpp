#include "../../../../include/TimberWolf/Graphics/OpenGL/GLFrameBuffer.hpp"

/**
 * @class tw::GLFrameBuffer
 *
 * Handle representing an OpenGL FBO (framebuffer object).
 */

/**
 * Default constructor. Creates an FBO on the graphics card.
 */
tw::GLFrameBuffer::GLFrameBuffer () {

    glGenFramebuffers(1, &m_id);

}

/**
 * Constructor taking in an ID to an existing FBO. This should only be used to
 * create a handle to an FBO created manually.
 *
 * @param id FBO ID
 */
tw::GLFrameBuffer::GLFrameBuffer (GLuint id)
: m_id(id) {}

/**
 * Get the ID of the FBO on the graphics card.
 *
 * @return FBO ID
 */
tw::GLFrameBuffer::~GLFrameBuffer () {

    glDeleteFramebuffers(1, &m_id);

}

 /**
  * Destructor. Deletes FBO on the graphics card if it is not in use.
  */
GLuint tw::GLFrameBuffer::getId () const {

    return m_id;

}

 /**
  * Bind the FBO (make it the currently selected FBO).
  */
void tw::GLFrameBuffer::bind () {

    glBindFramebuffer(GL_FRAMEBUFFER, m_id);

}

/**
 * Unbind the currently bound FBO (bind null FBO).
 */
void tw::GLFrameBuffer::unbind () {

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}
