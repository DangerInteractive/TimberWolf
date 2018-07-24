#include "../../../include/TimberWolf/World/PhysicsEntityComponent.hpp"

void tw::PhysicsEntityComponent::update (double deltaTime) {

    auto entity = getEntity();
    float floatDeltaTime = static_cast<float>(deltaTime);

    if (entity != nullptr) {

        entity->translate(m_velocity * floatDeltaTime);
        entity->rotate(m_angularVelocity * floatDeltaTime);

    }

    if (m_gravityEnabled) {
        processGravity();
    }

    if (m_dragEnabled) {
        processDrag();
    }

}

tw::Vertex tw::PhysicsEntityComponent::getVelocity () const {

    return m_velocity;

}

const tw::Vertex& tw::PhysicsEntityComponent::getVelocityRef () const {

    return m_velocity;

}

float tw::PhysicsEntityComponent::getVelocityX () const {

    return m_velocity.getX();

}

float tw::PhysicsEntityComponent::getVelocityY () const {

    return m_velocity.getY();

}

float tw::PhysicsEntityComponent::getVelocityZ () const {

    return m_velocity.getZ();

}

tw::PhysicsEntityComponent& tw::PhysicsEntityComponent::setVelocity (const Vertex& velocity) {

    m_velocity = velocity;
    return *this;

}

tw::PhysicsEntityComponent& tw::PhysicsEntityComponent::setVelocity (float x, float y, float z) {

    setVelocityX(x);
    setVelocityY(y);
    setVelocityZ(z);
    return *this;

}

tw::PhysicsEntityComponent& tw::PhysicsEntityComponent::setVelocityX (float x) {

    m_velocity.setX(x);
    return *this;

}

tw::PhysicsEntityComponent& tw::PhysicsEntityComponent::setVelocityY (float y) {

    m_velocity.setY(y);
    return *this;

}

tw::PhysicsEntityComponent& tw::PhysicsEntityComponent::setVelocityZ (float z) {

    m_velocity.setZ(z);
    return *this;

}

tw::PhysicsEntityComponent& tw::PhysicsEntityComponent::accelerate (const Vertex& velocity) {

    m_velocity += velocity;
    return *this;

}

tw::PhysicsEntityComponent& tw::PhysicsEntityComponent::accelerate (float x, float y, float z) {

    m_velocity += Vertex(x, y, z);
    return *this;

}

tw::PhysicsEntityComponent& tw::PhysicsEntityComponent::accelerate (float velocity) {

    auto magnitude = m_velocity.getVec3().length();
    auto multiplier = (magnitude + velocity) / magnitude;

    setVelocityX(getVelocityX() * multiplier);
    setVelocityY(getVelocityY() * multiplier);
    setVelocityZ(getVelocityZ() * multiplier);

    return *this;

}

tw::PhysicsEntityComponent& tw::PhysicsEntityComponent::accelerateX (float velocity) {

    m_velocity.setX(m_velocity.getX() + velocity);
    return *this;

}

tw::PhysicsEntityComponent& tw::PhysicsEntityComponent::accelerateY (float velocity) {

    m_velocity.setY(m_velocity.getY() + velocity);
    return *this;

}

tw::PhysicsEntityComponent& tw::PhysicsEntityComponent::accelerateZ (float velocity) {

    m_velocity.setZ(m_velocity.getZ() + velocity);
    return *this;

}
