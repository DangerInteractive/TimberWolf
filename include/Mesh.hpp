#ifndef H_TW_MESH
#define H_TW_MESH

#include <vector>
#include <GL/glew.h>
#include "Vertex.hpp"
#include "TexturePoint.hpp"
#include "GLBufferable.hpp"

namespace tw {
class Mesh : public GLBufferable {

public:

    enum AttribIndex {
        ATTRIB_VERTEX = 0,
        ATTRIB_INDEX = 1,
        ATTRIB_TEXTURE = 2
    };

    Mesh () = default;
    explicit Mesh (Vertex...);
    explicit Mesh (const std::vector<Vertex>&);
    Mesh (const std::vector<Vertex>&, unsigned int...);
    Mesh (const std::vector<Vertex>&, const std::vector<unsigned int>&);
    Mesh (const std::vector<Vertex>&, const std::vector<unsigned int>&, const std::vector<TexturePoint>&);
    virtual ~Mesh () = default;

    Mesh (Mesh&&) = default;
    Mesh& operator = (Mesh&&) = default;

    Mesh (const Mesh&) = default;
    Mesh& operator = (const Mesh&) = default;

protected:

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<TexturePoint> m_texturePoints;

};
}

#endif
