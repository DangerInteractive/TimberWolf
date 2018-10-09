#ifndef TW_CLASS_MESH
#define TW_CLASS_MESH

/**
 * @file
 *
 * Header file for the tw::Mesh class.
 */

#include <memory>
#include <stdexcept>
#include <vector>

#include "../Core/Normal.hpp"
#include "../Core/Vertex.hpp"

#include "GraphicsBufferable.hpp"
#include "MeshHandle.hpp"
#include "TexturePoint.hpp"

namespace tw {
class Mesh : public GraphicsBufferable {

public:

    enum AttribIndex {
        ATTRIB_VERTEX = 0,
        ATTRIB_INDEX = 1,
        ATTRIB_NORMAL = 2,
        ATTRIB_TEXTURE = 3
    };

    enum AttribFlag {
        FLAG_VERTEX = ATTRIB_0,
        FLAG_INDEX = ATTRIB_1,
        FLAG_NORMAL = ATTRIB_2,
        FLAG_TEXTURE = ATTRIB_3
    };

    Mesh () = default;
    explicit Mesh (Vertex...);
    Mesh (bool, Vertex...);
    virtual ~Mesh () = default;

    Mesh (Mesh&&) = default;
    Mesh& operator = (Mesh&&) = default;

    Mesh (const Mesh&) = default;
    Mesh& operator = (const Mesh&) = default;

    bool isPersistent () const;
    bool hasHandle () const;
    bool hasOriginalData () const;

    void makePersistent ();
    void makeEphemeral ();

    MeshHandle* getHandle () const;
    void setHandle (std::unique_ptr<MeshHandle>&&);
    void setHandle (MeshHandle*);

    unsigned int getVertexCount () const;
    const std::vector<Vertex>& getVertices () const;
    const Vertex& getVertex (unsigned int) const;

    bool indexBufferEnabled () const;
    unsigned int getIndexCount () const;
    const std::vector<uint32_t>& getIndices () const;
    uint32_t getIndex (unsigned int) const;

    bool normalBufferEnabled () const;
    unsigned int getNormalCount () const;
    const std::vector<Normal>& getNormals () const;
    const Normal& getNormal (unsigned int) const;

    bool textureBufferEnabled () const;
    unsigned int getTexturePointCount () const;
    const std::vector<TexturePoint>& getTexturePoints () const;
    const TexturePoint& getTexturePoint (unsigned int) const;

    void addVertices (const Vertex&...);
    void addIndices (uint32_t...);
    void addNormals (const Normal&...);
    void addTexturePoints (const TexturePoint&...);

    void setVertex (unsigned int, const Vertex&);
    void setIndex (unsigned int, uint32_t);
    void setNormal (unsigned int, const Normal&);
    void setTexturePoint (unsigned int, const TexturePoint&);

    void clearVertices ();
    void clearIndices ();
    void clearNormals ();
    void clearTexturePoints ();

    void enableIndexBuffer ();
    void disableIndexBuffer ();

    void enableNormalBuffer ();
    void disableNormalBuffer ();

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

    void eraseOriginalData ();

    bool m_persist {false};
    std::unique_ptr<MeshHandle> m_handle {nullptr};

    std::vector<Vertex> m_vertices {};

    bool m_indexBufferEnabled {false};
    std::vector<uint32_t> m_indices {};

    bool m_normalBufferEnabled {false};
    std::vector<Normal> m_normals {};

    bool m_textureBufferEnabled {false};
    std::vector<TexturePoint> m_texturePoints {};

};
}

#endif
