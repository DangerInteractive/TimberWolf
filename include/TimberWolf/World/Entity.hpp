#ifndef TW_CLASS_ENTITY
#define TW_CLASS_ENTITY

#include <map>
#include <memory>
#include <vector>

#include "../Core/Rotation.hpp"
#include "../Core/Vector3.hpp"
#include "../Core/Vertex.hpp"

#include "EntityComponent.hpp"

namespace tw {
class Entity {

public:

    Entity () = default;
    virtual ~Entity () = default;

    Entity (Entity&&) = default;
    Entity& operator = (Entity&&) = default;

    Entity (const Entity&) = default;
    Entity& operator = (const Entity&) = default;

    virtual void update (double);

    // translation
    Vertex getPosition () const;
    const Vertex& getPositionRef () const;
    float getPositionX () const;
    float getPositionY () const;
    float getPositionZ () const;

    void setPosition (const Vertex&);
    void setPosition (float, float, float);
    void setPositionX (float);
    void setPositionY (float);
    void setPositionZ (float);

    void translate (const Vertex&);
    void translate (float, float, float);
    void translateX (float);
    void translateY (float);
    void translateZ (float);

    // rotation
    Rotation getOrientation () const;
    const Rotation& getOrientationRef () const;

    void setOrientation (const Rotation&);
    void setOrientationRadians (float, const Vertex&);
    void setOrientationDegrees (float, const Vertex&);

    void rotate (const Rotation&);
    void rotateRadians (float, const Vertex&);
    void rotateDegrees (float, const Vertex&);

    // scaling
    Vertex getScale () const;
    const Vertex& getScaleRef () const;
    float getScaleX () const;
    float getScaleY () const;
    float getScaleZ () const;

    void setScale (const Vertex&);
    void setScale (float, float, float);
    void setScale (float);
    void setScaleX (float);
    void setScaleY (float);
    void setScaleZ (float);

    void scale (const Vertex&);
    void scale (float, float, float);
    void scale (float);
    void scaleX (float);
    void scaleY (float);
    void scaleZ (float);

private:

    Vertex m_position {0.f, 0.f, 0.f};
    Rotation m_orientation {};
    Vector3 m_scale = {1.f, 1.f, 1.f};

};
}

#endif
