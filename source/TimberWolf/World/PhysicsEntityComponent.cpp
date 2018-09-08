#include "../../../include/TimberWolf/World/PhysicsEntityComponent.hpp"

void tw::PhysicsEntityComponent::update (double deltaTime) {

    auto entity = getEntity();
    float floatDeltaTime = static_cast<float>(deltaTime);

    if (entity != nullptr) {

        entity->translate(m_velocity * floatDeltaTime);
        entity->rotate(m_angularVelocity.getQuaternion() * floatDeltaTime);

    }

    if (m_gravityEnabled) {
        processGravity(deltaTime);
    }

    if (m_dragEnabled) {
        processDrag(deltaTime);
    }

}

tw::Vector3 tw::PhysicsEntityComponent::getVelocity () const {

    return m_velocity;

}

const tw::Vector3& tw::PhysicsEntityComponent::getVelocityRef () const {

    return m_velocity;

}

float tw::PhysicsEntityComponent::getVelocityX () const {

    return m_velocity.x;

}

float tw::PhysicsEntityComponent::getVelocityY () const {

    return m_velocity.y;

}

float tw::PhysicsEntityComponent::getVelocityZ () const {

    return m_velocity.z;

}

tw::PhysicsEntityComponent& tw::PhysicsEntityComponent::setVelocity (const Vector3& velocity) {

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

    m_velocity.x = x;
    return *this;

}

tw::PhysicsEntityComponent& tw::PhysicsEntityComponent::setVelocityY (float y) {

    m_velocity.y = y;
    return *this;

}

tw::PhysicsEntityComponent& tw::PhysicsEntityComponent::setVelocityZ (float z) {

    m_velocity.z = z;
    return *this;

}

tw::PhysicsEntityComponent& tw::PhysicsEntityComponent::accelerate (const Vector3& velocity) {

    m_velocity += velocity;
    return *this;

}

tw::PhysicsEntityComponent& tw::PhysicsEntityComponent::accelerate (float x, float y, float z) {

    m_velocity += Vector3(x, y, z);
    return *this;

}

tw::PhysicsEntityComponent& tw::PhysicsEntityComponent::accelerate (float velocity) {

    auto magnitude = m_velocity.length();
    auto multiplier = (magnitude + velocity) / magnitude;

    setVelocityX(getVelocityX() * multiplier);
    setVelocityY(getVelocityY() * multiplier);
    setVelocityZ(getVelocityZ() * multiplier);

    return *this;

}

tw::PhysicsEntityComponent& tw::PhysicsEntityComponent::accelerateX (float velocity) {

    m_velocity.x += velocity;
    return *this;

}

tw::PhysicsEntityComponent& tw::PhysicsEntityComponent::accelerateY (float velocity) {

    m_velocity.y += velocity;
    return *this;

}

tw::PhysicsEntityComponent& tw::PhysicsEntityComponent::accelerateZ (float velocity) {

    m_velocity.z += velocity;
    return *this;

}

tw::PhysicsEntityComponent& tw::PhysicsEntityComponent::multiplyVelocity (const Vector3& multiplier) {

    m_velocity *= multiplier;
    return *this;

}

tw::PhysicsEntityComponent& tw::PhysicsEntityComponent::multiplyVelocity (float x, float y, float z) {

    setVelocityX(getVelocityX() * x);
    setVelocityY(getVelocityY() * y);
    setVelocityZ(getVelocityZ() * z);

    return *this;

}

tw::Rotation tw::PhysicsEntityComponent::getAngularVelocity () const {

    return m_angularVelocity;

}

const tw::Rotation& tw::PhysicsEntityComponent::getAngularVelocityRef () const {

    return m_angularVelocity;

}

tw::PhysicsEntityComponent& tw::PhysicsEntityComponent::spin (const Rotation& spin) {

    m_angularVelocity.rotateBy(spin);
    return *this;

}

tw::PhysicsEntityComponent& tw::PhysicsEntityComponent::spinRadians (float radians, const Vector3& angleAxis) {

    m_angularVelocity.rotateByRadians(radians, angleAxis);
    return *this;

}

tw::PhysicsEntityComponent& tw::PhysicsEntityComponent::spinDegrees (float degrees, const Vector3& angleAxis) {

    m_angularVelocity.rotateByDegrees(degrees, angleAxis);
    return *this;

}

tw::Vector3 tw::PhysicsEntityComponent::getGravity () const {

    return {0.f, -9.807f, 0.f}; // TODO: replace this, this is just earth-ish gravity for now

}

float tw::PhysicsEntityComponent::getResistance () const {

    return 0.25;

}

void tw::PhysicsEntityComponent::processGravity (double deltaTime) {

    m_velocity += getGravity() * static_cast<float>(deltaTime);

}

void tw::PhysicsEntityComponent::processDrag (double deltaTime) {

    m_velocity *= 1.f - (getResistance() * deltaTime);

}
