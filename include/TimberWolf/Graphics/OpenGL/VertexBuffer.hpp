#ifndef H_TW_VERTEXBUFFER
#define H_TW_VERTEXBUFFER

/**
 * @file
 *
 * Header file for the tw::VertexBuffer class.
 */

#include <GL/glew.h>

namespace tw {
class VertexBuffer {

public:

    VertexBuffer ();
    explicit VertexBuffer (GLuint);
    ~VertexBuffer ();

    VertexBuffer (VertexBuffer&&) = default;
    VertexBuffer& operator = (VertexBuffer&&) = default;

    VertexBuffer (const VertexBuffer&) = delete; // not copyable
    VertexBuffer& operator = (const VertexBuffer&) = delete;

    GLuint getId () const;

    void bind ();
    static void unbind ();

private:

    GLuint m_id {0};

};
}

#endif
