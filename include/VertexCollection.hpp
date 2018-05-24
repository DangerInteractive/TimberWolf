#ifndef H_TW_VERTEXCOLLECTION
#define H_TW_VERTEXCOLLECTION

#include <vector>
#include <GL/glew.h>
#include "GLBufferable.hpp"
#include "Vertex.hpp"

namespace tw {
class VertexCollection : public GLBufferable {

public:

    VertexCollection () = default;
    explicit VertexCollection (const std::vector<Vertex>&);
    explicit VertexCollection (std::vector<Vertex>&&);
    explicit VertexCollection (Vertex...);
    virtual ~VertexCollection () = default;

    VertexCollection (VertexCollection&&) = default;
    VertexCollection& operator = (VertexCollection&&) = default;

    VertexCollection (const VertexCollection&) = default;
    VertexCollection& operator = (const VertexCollection&) = default;

    Vertex get (unsigned int) const;
    float getX (unsigned int) const;
    float getY (unsigned int) const;
    float getZ (unsigned int) const;

    void set (const std::vector<Vertex>&);
    void set (std::vector<Vertex>&&);
    void set (Vertex...);

    bool setVertex (unsigned int, Vertex);
    bool setVertexX (unsigned int, float);
    bool setVertexY (unsigned int, float);
    bool setVertexZ (unsigned int, float);

    void add (Vertex...);
    bool remove (unsigned int);
    void clear ();

    // GLBufferable interface methods
    virtual void* getDataPointer () override;
    virtual GLsizei getDataBytes () override;
    virtual GLuint getSegmentCount () override;
    virtual GLint getSegmentSize (unsigned int = 0) override;
    virtual GLenum getDataType (unsigned int = 0) override;
    virtual GLsizei getDataTypeBytes (unsigned int = 0) override;
    virtual GLboolean isNormalized (unsigned int = 0) override;
    virtual GLsizei getStride (unsigned int = 0) override;
    virtual GLsizei getOffset (unsigned int = 0) override;

private:

    std::vector<Vertex> m_vertices {};

};
}

#endif
