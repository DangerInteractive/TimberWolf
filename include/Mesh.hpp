#ifndef H_TW_MESH
#define H_TW_MESH

#include <vector>
#include <GL/glew.h>

namespace tw {
template <typename T = float, GLint Size = 3, GLenum Type = GL_FLOAT, GLboolean Normalized = GL_FALSE, GLsizei Stride = 0>
class Mesh {

public:

    Mesh () = default;
    explicit Mesh (std::initializer_list<T> initializerList)
    : m_data(std::vector<T>(initializerList)) {}
    explicit Mesh (const std::vector<T>& data)
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

    const std::vector<T>& getVertexVector () const {
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

    std::vector<T> m_data;

};
}

#endif
