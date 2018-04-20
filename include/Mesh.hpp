#ifndef H_CLASS_MESH
#define H_CLASS_MESH

#include <vector>
#include <GL/glew.h>

namespace tw {
template <typename T = float, GLint Size = 3, GLenum Type = GL_FLOAT, GLboolean Normalized = false, GLsizei Stride = 0>
class Mesh {

public:

    Mesh () = default;
    explicit Mesh (T&& args...) {
        m_vertices.emplace_back(std::forward<T>(args));
    }
    ~Mesh () = default;

    Mesh (Mesh&&) = default;
    Mesh& operator = (Mesh&&) = default;

    Mesh (const Mesh&) = default;
    Mesh& operator = (const Mesh&) = default;

    constexpr GLenum getVertexSize () const noexcept {
        return Size;
    }

    constexpr GLenum getDataType () const noexcept {
        return Type;
    }

    constexpr GLboolean isNormalized () const noexcept {
        return Normalized;
    }

    constexpr GLsizei getVertexStride () const noexcept {
        return Stride;
    }

    const std::vector<T>& getVertexVector () const {
        return m_vertices;
    }

    const T* getVertexPointer () const {
        return &m_vertices.front();
    }

    unsigned int getVertexCount () const {
        return m_vertices.size();
    }

protected:

    std::vector<T[Size + Stride]> m_vertices;

};
}

#endif
