#ifndef TW_CLASS_VELOCITYENTITYCOMPONENT
#define TW_CLASS_VELOCITYENTITYCOMPONENT

#include "../Core/Rotation.hpp"
#include "../Core/Vertex.hpp"

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
    Vertex getVelocity () const;
    const Vertex& getVelocityRef () const;
    float getVelocityX () const;
    float getVelocityY () const;
    float getVelocityZ () const;

    PhysicsEntityComponent& setVelocity (const Vertex&);
    PhysicsEntityComponent& setVelocity (float, float, float);
    PhysicsEntityComponent& setVelocityX (float);
    PhysicsEntityComponent& setVelocityY (float);
    PhysicsEntityComponent& setVelocityZ (float);

    PhysicsEntityComponent& accelerate (const Vertex&);
    PhysicsEntityComponent& accelerate (float, float, float);
    PhysicsEntityComponent& accelerate (float);
    PhysicsEntityComponent& accelerateX (float);
    PhysicsEntityComponent& accelerateY (float);
    PhysicsEntityComponent& accelerateZ (float);

    PhysicsEntityComponent& multiplyVelocity (const Vertex&);
    PhysicsEntityComponent& multiplyVelocity (float, float, float);
    PhysicsEntityComponent& multiplyVelocity (float);

    // angular velocity (rotation through time)
    Rotation getAngularVelocity () const;
    const Rotation& getAngularVelocityRef () const;

    PhysicsEntityComponent& setAngularVelocity (const Rotation&);
    PhysicsEntityComponent& setAngularVelocityRadians (float, const Vertex&);
    PhysicsEntityComponent& setAngularVelocityDegrees (float, const Vertex&);

    PhysicsEntityComponent& spin (const Rotation&);
    PhysicsEntityComponent& spinRadians (float, const Vertex&);
    PhysicsEntityComponent& spinDegrees (float, const Vertex&);

protected:

    void processGravity ();
    void processDrag ();

private:

    Vertex m_velocity {0.f, 0.f, 0.f};
    Rotation m_angularVelocity {};

    bool m_gravityEnabled {false};
    bool m_dragEnabled {false};

};
}

#endif
