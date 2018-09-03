#ifndef TW_CLASS_GLVERTEXBUFFER
#define TW_CLASS_GLVERTEXBUFFER

/**
 * @file
 *
 * Header file for the tw::GLVertexBuffer class.
 */

#include <GL/glew.h>

namespace tw {
class GLVertexBuffer {

public:

    GLVertexBuffer ();
    explicit GLVertexBuffer (GLuint);
    ~GLVertexBuffer ();

    GLVertexBuffer (GLVertexBuffer&&) = default;
    GLVertexBuffer& operator = (GLVertexBuffer&&) = default;

    GLVertexBuffer (const GLVertexBuffer&) = delete; // not copyable
    GLVertexBuffer& operator = (const GLVertexBuffer&) = delete;

    GLuint getId () const;

    void bind ();
    static void unbind ();

private:

    GLuint m_id {0};

};
}

#endif
