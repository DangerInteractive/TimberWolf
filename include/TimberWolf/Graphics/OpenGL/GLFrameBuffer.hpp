#ifndef TW_CLASS_GLFRAMEBUFFER
#define TW_CLASS_GLFRAMEBUFFER

/**
 * @file
 *
 * Header file for the tw::GLFrameBuffer class.
 */

#include <GL/glew.h>

namespace tw {
class GLFrameBuffer {

public:

    GLFrameBuffer ();
    explicit GLFrameBuffer (GLuint);
    ~GLFrameBuffer ();

    GLFrameBuffer (GLFrameBuffer&&) = default;
    GLFrameBuffer& operator = (GLFrameBuffer&&) = default;

    GLFrameBuffer (const GLFrameBuffer&) = delete;
    GLFrameBuffer& operator = (const GLFrameBuffer&) = delete;

    GLuint getId () const;

    void bind ();
    static void unbind ();

private:

    GLuint m_id {0};

};
}

#endif
