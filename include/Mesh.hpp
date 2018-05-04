#ifndef H_TW_MESH
#define H_TW_MESH

#include <array>
#include <GL/glew.h>

namespace tw {
template <typename T = float, GLint Size = 3, GLenum Type = GL_FLOAT, GLboolean Normalized = GL_FALSE, GLsizei Stride = 0>
class Mesh {

public:

    Mesh () = default;
    explicit Mesh (T&& data...)
    : m_data({{std::forward<T>(data)}}) {}
    explicit Mesh (const std::array<T, Size*(3+Stride)>& data)
    : m_data(data) {}
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

    const std::array<T, Size*(3+Stride)>& getVertexData () const {
        return m_data;
    }

    const T* getVertexPointer () const {
        return &m_data.front();
    }

    unsigned int getVertexCount () const {
        return m_data.size() / (static_cast<int>(Size) + static_cast<int>(Stride));
    }

    unsigned int getDataSize () const {
        return sizeof(T) * m_data.size();
    }

protected:

    std::array<T, Size*(3+Stride)> m_data;

};
}

#endif
