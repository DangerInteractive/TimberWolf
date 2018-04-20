#ifndef H_CLASS_VERTEXARRAY
#define H_CLASS_VERTEXARRAY

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

    template <typename ...T>
    void storeBuffer (T&&... args) {

        bind();
        glVertexAttribPointer(std::forward<T>(args)...);
        unbind();

    }

    void storeBuffer (GLuint, VertexBuffer&);

    void bind ();
    void unbind ();

private:

    GLuint m_id {0};

};
}

#endif
