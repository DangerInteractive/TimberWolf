#ifndef TW_CLASS_GLVERTEXARRAY
#define TW_CLASS_GLVERTEXARRAY

/**
 * @file
 *
 * Header file for the tw::GLVertexArray class.
 */

#include <GL/glew.h>
#include "GLVertexBuffer.hpp"

namespace tw {
class GLVertexArray {

public:

    GLVertexArray ();
    explicit GLVertexArray (GLuint);
    ~GLVertexArray ();

    GLVertexArray (GLVertexArray&&) = default;
    GLVertexArray& operator = (GLVertexArray&&) = default;

    GLVertexArray (const GLVertexArray&) = delete; // not copyable
    GLVertexArray& operator = (const GLVertexArray&) = delete;

    GLuint getId () const;

    void bind ();
    static void unbind ();

private:

    GLuint m_id {0};

};
}

#endif
