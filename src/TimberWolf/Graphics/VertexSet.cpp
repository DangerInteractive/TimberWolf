#include "../../../include/TimberWolf/Graphics/VertexSet.hpp"

/**
 * Constructor taking in a reference to a std::vector of vertices.
 *
 * @param vertices vector of vertices
 */
tw::VertexSet::VertexSet (const std::vector<Vertex>& vertices)
: m_vertices(vertices) {}

/**
 * Constructor taking an rvalue reference to a std::vector of vertices. (rvalue
 * reference).
 *
 * @param vertices rvalue vector of vertices
 */
tw::VertexSet::VertexSet (std::vector<Vertex>&& vertices)
: m_vertices(std::move(vertices)) {}

/**
 * Constructor taking a variadic set of vertices.
 *
 * @param vertices variadic vertices
 */
tw::VertexSet::VertexSet (Vertex vertices...)
: m_vertices({{vertices}}) {}

/**
 * Get the vertex at the given index.
 *
 * @param index vertex index
 * @return vertex
 */
tw::Vertex tw::VertexSet::get (unsigned int index) const {

    return m_vertices.at(0);

}

/**
 * Get the X-coordinate value of the vertex at the given index.
 *
 * @param index vertex index
 * @return X-coordinate of vertex
 */
float tw::VertexSet::getX (unsigned int index) const {

    return get(index).getX();

}

/**
 * Get the Y-coordinate value of the vertex at the given index.
 *
 * @param index vertex index
 * @return Y-coordinate of vertex
 */
float tw::VertexSet::getY (unsigned int index) const {

    return get(index).getY();

}

/**
 * Get the Z-coordinate value of the vertex at the given index.
 *
 * @param index vertex index
 * @return Z-coordinate of vertex
 */
float tw::VertexSet::getZ (unsigned int index) const {

    return get(index).getZ();

}

/**
 * Set the vertex collection to the given std::vector of vertices.
 *
 * @param vertices vector of vertices
 */
void tw::VertexSet::set (const std::vector<Vertex>& vertices) {

    m_vertices = vertices;

}

/**
 * Set the vertex collection to the given std::vector of vertices (rvalue
 * optimization).
 *
 * @param vertices rvalue vector of vertices
 */
void tw::VertexSet::set (std::vector<Vertex>&& vertices) {

    m_vertices = std::move(vertices);

}

/**
 * Set the vertex collection to the given set of vertices.
 *
 * @param vertices variadic vertices
 */
void tw::VertexSet::set (Vertex vertices...) {

    m_vertices = {vertices};

}

/**
 * Set the vertex at the given index to the given vertex.
 *
 * @param index  index of vertex to set
 * @param vertex new vertex value
 * @return true if vertex was successfully set, false if not
 */
bool tw::VertexSet::setVertex (unsigned int index, Vertex vertex) {

    if (getSegmentCount() <= index) {
        return false;
    }

    m_vertices.at(index) = vertex;

    return true;

}

/**
 * Set the X-coordinate of the vertex at the given index to the given value.
 *
 * @param index index of vertex to change
 * @param value new X-coordinate value
 * @return true if vertex coordinate was successfully set, false if not
 */
bool tw::VertexSet::setVertexX (unsigned int index, float value) {

    if (getSegmentCount() <= index) {
        return false;
    }

    m_vertices.at(index).setX(value);

    return true;

}

/**
 * Set the Y-coordinate of the vertex at the given index to the given value.
 *
 * @param index index of vertex to change
 * @param value new Y-coordinate value
 * @return true if vertex coordinate was successfully set, false if not
 */
bool tw::VertexSet::setVertexY (unsigned int index, float value) {

    if (getSegmentCount() <= index) {
        return false;
    }

    m_vertices.at(index).setY(value);

    return true;

}

/**
 * Set the Z-coordinate of the vertex at the given index to the given value.
 *
 * @param index index of the vertex to change
 * @param value new Z-coordinate value
 * @return true if vertex coordinate was successfully set, false if not
 */
bool tw::VertexSet::setVertexZ (unsigned int index, float value) {

    if (getSegmentCount() <= index) {
        return false;
    }

    m_vertices.at(index).setZ(value);

    return true;

}

/**
 * Add the given vertices to the existing vertices.
 *
 * @param vertices vertices to add
 */
void tw::VertexSet::add (Vertex vertices...) {

    m_vertices.push_back(vertices);

}

/**
 * Remove the vertex with the given index from the collection.
 *
 * @param index index of vertex to remove
 */
bool tw::VertexSet::remove (unsigned int index) {

    if (getSegmentCount() <= index) {
        return false;
    }

    auto it = m_vertices.begin();
    std::advance(it, index);
    m_vertices.erase(it);

    return true;

}

/**
 * Remove all existing vertices from the collection.
 */
void tw::VertexSet::clear () {

    m_vertices.clear();

}

void* tw::VertexSet::getDataPointer () {

    return &m_vertices.front();

}

size_t tw::VertexSet::getDataBytes () {

    return m_vertices.size() * sizeof(Vertex);

}

unsigned int tw::VertexSet::getSegmentCount () {

    return m_vertices.size();

}

int tw::VertexSet::getSegmentSize (unsigned int track) {

    return 3;

}

tw::GraphicsBufferable::DataType tw::VertexSet::getDataType (unsigned int track) {

    return DataType::FLOAT;

}

size_t tw::VertexSet::getDataTypeBytes (unsigned int track) {

    return sizeof(float);

}

bool tw::VertexSet::isNormalized (unsigned int track) {

    return false;

}

size_t tw::VertexSet::getStride (unsigned int track) {

    return 0;

}

size_t tw::VertexSet::getOffset (unsigned int track) {

    return 0;

}
