#ifndef TW_CLASS_MESH
#define TW_CLASS_MESH

/**
 * @file
 *
 * Header file for the tw::Mesh class.
 */

#include <memory>
#include <vector>

#include <GL/glew.h>

#include "../Core/Vertex.hpp"

#include "GraphicsBufferable.hpp"
#include "TexturePoint.hpp"

namespace tw {
class Mesh : public GraphicsBufferable {

public:

    enum AttribIndex {
        ATTRIB_VERTEX = 0,
        ATTRIB_INDEX = 1,
        ATTRIB_TEXTURE = 2
    };

    enum AttribFlag {
        FLAG_VERTEX = GraphicsBufferable::ToBuffer::ATTRIB_0,
        FLAG_INDEX = GraphicsBufferable::ToBuffer::ATTRIB_1,
        FLAG_TEXTURE = GraphicsBufferable::ToBuffer::ATTRIB_2
    };

    Mesh () = default;
    explicit Mesh (Vertex...);
    virtual ~Mesh () = default;

    Mesh (Mesh&&) = default;
    Mesh& operator = (Mesh&&) = default;

    Mesh (const Mesh&) = default;
    Mesh& operator = (const Mesh&) = default;

    unsigned int getVertexCount () const;
    const std::vector<Vertex>& getVertices () const;
    const Vertex& getVertex (unsigned int) const;

    bool indexBufferEnabled () const;
    unsigned int getIndexCount () const;
    const std::vector<uint32_t>& getIndices () const;
    uint32_t getIndex (unsigned int) const;

    bool textureBufferEnabled () const;
    unsigned int getTexturePointCount () const;
    const std::vector<TexturePoint>& getTexturePoints () const;
    const TexturePoint& getTexturePoint (unsigned int) const;

    void addVertices (const Vertex&...);
    void addIndices (uint32_t...);
    void addTexturePoints (const TexturePoint&...);

    void setVertex (unsigned int, const Vertex&);
    void setIndex (unsigned int, uint32_t);
    void setTexturePoint (unsigned int, const TexturePoint&);

    void clearVertices ();
    void clearIndices ();
    void clearTexturePoints ();

    void enableIndexBuffer ();
    void disableIndexBuffer ();

    void enableTextureBuffer ();
    void disableTextureBuffer ();

    // implementations for GraphicsBufferable interface
    uint16_t getTracksToBuffer () override;
    void* getDataPointer (uint8_t = 0) override;
    size_t getDataBytes (uint8_t = 0) override;
    unsigned int getSegmentCount (uint8_t = 0) override;
    int32_t getSegmentSize (uint8_t = 0) override;
    GraphicsBufferable::DataType getDataType (uint8_t = 0) override;
    size_t getDataTypeBytes (uint8_t = 0) override;
    bool isNormalized (uint8_t = 0) override;
    size_t getStride (uint8_t = 0) override;
    size_t getOffset (uint8_t = 0) override;

protected:

    std::vector<Vertex> m_vertices;

    bool m_indexBufferEnabled = false;
    std::vector<uint32_t> m_indices;

    bool m_textureBufferEnabled = false;
    std::vector<TexturePoint> m_texturePoints;

};
}

#endif
