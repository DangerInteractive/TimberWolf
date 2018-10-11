#ifndef TW_CLASS_MESH
#define TW_CLASS_MESH

/**
 * @file
 *
 * Header file for the tw::Mesh class.
 */

#include <array>
#include <cstdint>
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

    typedef std::array<uint8_t, 3> JointBindingListType;
    typedef std::array<float, 3> JointWeightListType;

    enum AttribIndex {
        ATTRIB_VERTEX = 0,
        ATTRIB_INDEX = 1,
        ATTRIB_NORMAL = 2,
        ATTRIB_TEXTURE = 3,
        ATTRIB_JOINT_BINDING = 4,
        ATTRIB_JOINT_WEIGHT = 5
    };

    enum AttribFlag {
        FLAG_VERTEX = ATTRIB_0,
        FLAG_INDEX = ATTRIB_1,
        FLAG_NORMAL = ATTRIB_2,
        FLAG_TEXTURE = ATTRIB_3,
        FLAG_JOINT_BINDING = ATTRIB_4,
        FLAG_JOINT_WEIGHT = ATTRIB_5
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

    unsigned int getVertexDrawCount () const;

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

    bool skeletalBufferEnabled () const;
    unsigned int getJointBindingCount () const;
    unsigned int getJointWeightCount () const;
    const std::vector<JointBindingListType>& getJointBindings () const;
    const std::vector<JointWeightListType>& getJointWeights () const;
    const JointBindingListType& getJointBinding (unsigned int) const;
    const JointWeightListType& getJointWeight (unsigned int) const;

    void addVertices (const Vertex&...);
    void addIndices (uint32_t...);
    void addNormals (const Normal&...);
    void addTexturePoints (const TexturePoint&...);
    void addJointBindings (const JointBindingListType&...);
    void addJointWeights (const JointWeightListType&...);

    void setVertex (unsigned int, const Vertex&);
    void setIndex (unsigned int, uint32_t);
    void setNormal (unsigned int, const Normal&);
    void setTexturePoint (unsigned int, const TexturePoint&);
    void setJointBinding (unsigned int, const JointBindingListType&);
    void setJointWeight (unsigned int, const JointWeightListType&);

    void clearVertices ();
    void clearIndices ();
    void clearNormals ();
    void clearTexturePoints ();
    void clearJointBindings ();
    void clearJointWeights ();

    void enableIndexBuffer ();
    void disableIndexBuffer ();

    void enableNormalBuffer ();
    void disableNormalBuffer ();

    void enableTextureBuffer ();
    void disableTextureBuffer ();

    void enableSkeletalBuffer ();
    void disableSkeletalBuffer ();

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

    bool m_skeletalBufferEnabled {false};
    std::vector<JointBindingListType> m_jointBindings {};
    std::vector<JointWeightListType> m_jointWeights {};

};
}

#endif
