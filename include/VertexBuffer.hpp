#ifndef H_CLASS_VBO
#define H_CLASS_VBO

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

    void bind ();
    void unbind ();

private:

    GLuint m_id {0};

};
}

#endif
