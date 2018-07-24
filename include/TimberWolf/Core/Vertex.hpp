#ifndef H_TW_VERTEX
#define H_TW_VERTEX

/**
 * @file
 *
 * Header file for the tw::Vertex class.
 */

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace tw {
class Vertex {

public:

    Vertex () = default;
    Vertex (float, float);
    Vertex (float, float, float);
    Vertex (glm::vec3); // implicit
    Vertex (glm::vec4); // implicit
    ~Vertex () = default;

    Vertex (Vertex&&) = default;
    Vertex& operator = (Vertex&&) = default;

    Vertex (const Vertex&) = default;
    Vertex& operator = (const Vertex&) = default;

    glm::vec3 getVec3 () const;
    glm::vec4 getVec4 () const;
    float getX () const;
    float getY () const;
    float getZ () const;

    void setVec3 (glm::vec3);
    void setVec4 (glm::vec4);
    void setX (float);
    void setY (float);
    void setZ (float);

    operator glm::vec3 () const; // implicit
    operator glm::vec4 () const; // implicit

    // addition (translation)
    Vertex operator + (const Vertex&) const;
    Vertex& operator += (const Vertex&);

    // subtration (translation)
    Vertex operator - (const Vertex&) const;
    Vertex& operator -= (const Vertex&);

    // multiplication (scaling)
    Vertex operator * (const Vertex&) const;
    Vertex operator * (float) const;
    Vertex operator * (double) const;
    Vertex& operator *= (const Vertex&);
    Vertex& operator *= (float);
    Vertex& operator *= (double);

private:

    glm::vec3 m_vertex;

};
}

#endif
