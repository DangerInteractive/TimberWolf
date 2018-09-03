#ifndef TW_CLASS_VERTEXSET
#define TW_CLASS_VERTEXSET

/**
 * @file
 *
 * Header file for the tw::VertexSet class.
 */

#include <vector>
#include "GraphicsBufferable.hpp"
#include "../Core/Vertex.hpp"

namespace tw {
class VertexSet : public GraphicsBufferable {

public:

    VertexSet () = default;
    explicit VertexSet (const std::vector<Vertex>&);
    explicit VertexSet (std::vector<Vertex>&&);
    explicit VertexSet (Vertex...);
    virtual ~VertexSet () = default;

    VertexSet (VertexSet&&) = default;
    VertexSet& operator = (VertexSet&&) = default;

    VertexSet (const VertexSet&) = default;
    VertexSet& operator = (const VertexSet&) = default;

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
    virtual size_t getDataBytes () override;
    virtual unsigned int getSegmentCount () override;
    virtual int getSegmentSize (unsigned int = 0) override;
    virtual GraphicsBufferable::DataType getDataType (unsigned int = 0) override;
    virtual size_t getDataTypeBytes (unsigned int = 0) override;
    virtual bool isNormalized (unsigned int = 0) override;
    virtual size_t getStride (unsigned int = 0) override;
    virtual size_t getOffset (unsigned int = 0) override;

private:

    std::vector<Vertex> m_vertices {};

};
}

#endif
