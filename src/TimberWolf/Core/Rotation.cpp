#include "../../../include/TimberWolf/Core/Rotation.hpp"

tw::Rotation::Rotation (float radians, const Vertex& axisNormal) {

    rotateByRadians(radians, axisNormal);

}

const glm::quat& tw::Rotation::getQuaternion () const {

    return m_quaternion;

}

tw::Rotation& tw::Rotation::rotateByRadians (float radians, const Vertex& axisNormal) {

    m_quaternion *= glm::angleAxis(radians, axisNormal.getVec3());
    return *this;

}

tw::Rotation& tw::Rotation::rotateByDegrees (float degrees, const Vertex& axisNormal) {

    m_quaternion *= glm::angleAxis(glm::radians(degrees), axisNormal.getVec3());
    return *this;

}

tw::Rotation& tw::Rotation::rotateToRadians (float radians, const Vertex& axisNormal) {

    reset().rotateByRadians(radians, axisNormal);
    return *this;

}

tw::Rotation& tw::Rotation::rotateToDegrees (float degrees, const Vertex& axisNormal) {

    reset().rotateByDegrees(degrees, axisNormal);
    return *this;

}

tw::Rotation& tw::Rotation::reset () {

    m_quaternion = {};
    return *this;

}

tw::Rotation::operator glm::quat () const {

    return getQuaternion();

}

tw::Rotation tw::Rotation::operator * (float right) const {

    return m_quaternion * right;

}

tw::Rotation& tw::Rotation::operator *= (float right) {

    m_quaternion *= right;
    return *this;

}
