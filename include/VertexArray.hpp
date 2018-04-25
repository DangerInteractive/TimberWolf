#ifndef H_TW_VERTEXARRAY
#define H_TW_VERTEXARRAY

#include <GL/glew.h>
#include "VertexBuffer.hpp"
#include "Mesh.hpp"

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

    void storeBuffer (GLuint, VertexBuffer&);

    void enableAttribute (GLuint);
    void disableAttribute (GLuint);

    void bind ();
    void unbind ();

private:

    GLuint m_id {0};

};
}

#endif