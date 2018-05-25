#include "../../../include/TimberWolf/Graphics/Vertex.hpp"

/**
 * Get a 3-dimensional vector of vertex coordinates.
 *
 * @return 3-dimensional vector of vertex coordinates
 */
glm::vec3 tw::Vertex::getVec3 () const {

    return m_vertex;

}

/**
 * Get a 4-dimensional vector of vertex coordinates.
 *
 * @return 4-dimensional vector of vertex coordinates
 */
glm::vec4 tw::Vertex::getVec4 () const {

    return glm::vec4(m_vertex.x, m_vertex.y, m_vertex.z, 1.0);

}

/**
 * Get the X-coordinate of the vertex.
 *
 * @return X-coordinate
 */
float tw::Vertex::getX () const {

    return m_vertex.x;

}

/**
 * Get the Y-coordinate of the vertex.
 *
 * @return Y-coordinate
 */
float tw::Vertex::getY () const {

    return m_vertex.y;

}

/**
 * Get the Z-coordinate of the vertex.
 *
 * @return Z-coordinate
 */
float tw::Vertex::getZ () const {

    return m_vertex.z;

}

/**
 * Set the 3-dimensional vector of vertex coordinates to the given value. Note
 * that values should be in (x, y, z) order.
 *
 * @param vertex new 3-dimensional vector of vertex coordinates
 */
void tw::Vertex::setVec3 (glm::vec3 vertex) {

    m_vertex = vertex;

}

/**
 * Set the 4-dimensional vector of vertex coordinates to the given value. Note
 * that the values should be in (x, y, z, w) order and w will be ignored.
 */
void tw::Vertex::setVec4 (glm::vec4 vertex) {

    m_vertex = glm::vec3(vertex.x, vertex.y, vertex.z);

}

/**
 * Set the X-coordinate value of the vertex.
 *
 * @param x new X-coordinate
 */
void tw::Vertex::setX (float x) {

    m_vertex.x = x;

}

/**
 * Set the Y-coordinate value of the vertex.
 *
 * @param y new Y-coordinate
 */
void tw::Vertex::setY (float y) {

    m_vertex.y = y;

}

/**
 * Set the Z-coordinate value of the vertex.
 *
 * @param z new Z-coordinate
 */
void tw::Vertex::setZ (float z) {

    m_vertex.z = z;

}

/**
 * Implicit conversion from tw::Vertex to glm::vec3.
 *
 * @return equivalent glm::vec3 object
 */
tw::Vertex::operator glm::vec3 () const {

    return getVec3();

}

/**
 * Implicit conversion from tw::Vertex to glm::vec4.
 *
 * @return equivalent glm::vec4 object
 */
tw::Vertex::operator glm::vec4 () const {

    return getVec4();

}
