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

    Entity& setPosition (const Vertex&);
    Entity& setPosition (float, float, float);
    Entity& setPositionX (float);
    Entity& setPositionY (float);
    Entity& setPositionZ (float);

    Entity& translate (const Vertex&);
    Entity& translate (float, float, float);
    Entity& translateX (float);
    Entity& translateY (float);
    Entity& translateZ (float);

    // rotation
    Rotation getOrientation () const;
    const Rotation& getOrientationRef () const;

    Entity& setOrientation (const Rotation&);
    Entity& setOrientationRadians (float, const Vertex&);
    Entity& setOrientationDegrees (float, const Vertex&);

    Entity& rotate (const Rotation&);
    Entity& rotateRadians (float, const Vertex&);
    Entity& rotateDegrees (float, const Vertex&);

    // scaling
    Vertex getScale () const;
    const Vertex& getScaleRef () const;
    float getScaleX () const;
    float getScaleY () const;
    float getScaleZ () const;

    Entity& setScale (const Vertex&);
    Entity& setScale (float, float, float);
    Entity& setScale (float);
    Entity& setScaleX (float);
    Entity& setScaleY (float);
    Entity& setScaleZ (float);

    Entity& scale (const Vertex&);
    Entity& scale (float, float, float);
    Entity& scale (float);
    Entity& scaleX (float);
    Entity& scaleY (float);
    Entity& scaleZ (float);

private:

    Vertex m_position {0.f, 0.f, 0.f};
    Rotation m_orientation {};
    Vector3 m_scale = {1.f, 1.f, 1.f};

};
}

#endif
