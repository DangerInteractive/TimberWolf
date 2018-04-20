#ifndef H_CLASS_VERTEXARRAY
#define H_CLASS_VERTEXARRAY

#include <GL/glew.h>

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

    void bind ();
    void unbind ();

private:

    GLuint m_id {0};

};
}

#endif
