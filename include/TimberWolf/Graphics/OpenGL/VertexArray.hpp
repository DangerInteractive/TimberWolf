#ifndef H_TW_VERTEXARRAY
#define H_TW_VERTEXARRAY

/**
 * @file
 *
 * Header file for the tw::VertexArray class.
 */

#include <GL/glew.h>
#include "VertexBuffer.hpp"

namespace tw {
class VertexArray {

public:

    VertexArray ();
    explicit VertexArray (GLuint);
    ~VertexArray ();

    VertexArray (VertexArray&&) = default;
    VertexArray& operator = (VertexArray&&) = default;

    VertexArray (const VertexArray&) = delete; // not copyable
    VertexArray& operator = (const VertexArray&) = delete;

    GLuint getId () const;

    void bind ();
    static void unbind ();

private:

    GLuint m_id {0};

};
}

#endif
