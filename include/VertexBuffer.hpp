#ifndef H_TW_VBO
#define H_TW_VBO

#include <vector>
#include <GL/glew.h>
#include "Mesh.hpp"

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

    GLint getVertexSize () const;
    GLenum getDataType () const;
    GLboolean isNormalized () const;
    GLsizei getVertexStride () const;

    template <typename T, GLint Size, GLenum Type, GLboolean Normalized, GLsizei Stride>
    void write (const Mesh<T, Size, Type, Normalized, Stride>& mesh) {

        m_vertexSize = Size;
        m_dataType = Type;
        m_normalized = Normalized;
        m_vertexStride = Stride;

        bind();
        glBufferData(GL_ARRAY_BUFFER, mesh.getVertexCount(), mesh.getVertexPointer(), GL_STATIC_DRAW);
        unbind();

    }

    void bind ();
    void unbind ();

private:

    GLuint m_id {0};

    GLint m_vertexSize {3}; // number of elements making up one vertex
    GLenum m_dataType {GL_FLOAT};
    GLboolean m_normalized {false};
    GLsizei m_vertexStride {0}; // number of values between vertices

};
}

#endif
