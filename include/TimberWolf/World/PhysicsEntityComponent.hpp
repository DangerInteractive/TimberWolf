#ifndef TW_CLASS_VELOCITYENTITYCOMPONENT
#define TW_CLASS_VELOCITYENTITYCOMPONENT

#include "../Core/Rotation.hpp"
#include "../Core/Vector3.hpp"

#include "Entity.hpp"
#include "EntityComponent.hpp"

namespace tw {
class PhysicsEntityComponent : public EntityComponent {

public:

    static constexpr char ID[] = "physics";

    PhysicsEntityComponent () = default;
    virtual ~PhysicsEntityComponent () = default;

    PhysicsEntityComponent (PhysicsEntityComponent&&) = default;
    PhysicsEntityComponent& operator = (PhysicsEntityComponent&&) = default;

    PhysicsEntityComponent (const PhysicsEntityComponent&) = default;
    PhysicsEntityComponent& operator = (const PhysicsEntityComponent&) = default;

    virtual void update (double);

    // velocity (translation through time)
    Vector3 getVelocity () const;
    const Vector3& getVelocityRef () const;
    float getVelocityX () const;
    float getVelocityY () const;
    float getVelocityZ () const;

    PhysicsEntityComponent& setVelocity (const Vector3&);
    PhysicsEntityComponent& setVelocity (float, float, float);
    PhysicsEntityComponent& setVelocityX (float);
    PhysicsEntityComponent& setVelocityY (float);
    PhysicsEntityComponent& setVelocityZ (float);

    PhysicsEntityComponent& accelerate (const Vector3&);
    PhysicsEntityComponent& accelerate (float, float, float);
    PhysicsEntityComponent& accelerate (float);
    PhysicsEntityComponent& accelerateX (float);
    PhysicsEntityComponent& accelerateY (float);
    PhysicsEntityComponent& accelerateZ (float);

    PhysicsEntityComponent& multiplyVelocity (const Vector3&);
    PhysicsEntityComponent& multiplyVelocity (float, float, float);
    PhysicsEntityComponent& multiplyVelocity (float);

    // angular velocity (rotation through time)
    Rotation getAngularVelocity () const;
    const Rotation& getAngularVelocityRef () const;

    PhysicsEntityComponent& setAngularVelocity (const Rotation&);
    PhysicsEntityComponent& setAngularVelocityRadians (float, const Vector3&);
    PhysicsEntityComponent& setAngularVelocityDegrees (float, const Vector3&);

    PhysicsEntityComponent& spin (const Rotation&);
    PhysicsEntityComponent& spinRadians (float, const Vector3&);
    PhysicsEntityComponent& spinDegrees (float, const Vector3&);

protected:

    virtual Vector3 getGravity () const;
    virtual float getResistance () const;

    virtual void processGravity (double deltaTime);
    virtual void processDrag (double deltaTime);

private:

    Vector3 m_velocity {0.f, 0.f, 0.f};
    Rotation m_angularVelocity {};

    bool m_gravityEnabled {false};
    bool m_dragEnabled {false};

};
}

#endif
