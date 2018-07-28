#include "../../../include/TimberWolf/Core/Rotation.hpp"

tw::Rotation::Rotation (float radians, const Vector3& axisNormal) {

    rotateByRadians(radians, axisNormal);

}

tw::Quaternion tw::Rotation::getQuaternion () const {

    return m_quaternion;

}

const tw::Quaternion& tw::Rotation::getQuaternionRef () const {

    return m_quaternion;

}

tw::Rotation& tw::Rotation::rotateBy (const Rotation& rotation) {

    m_quaternion *= rotation.getQuaternion();
    return *this;

}

tw::Rotation& tw::Rotation::rotateByRadians (float radians, const Vector3& axisNormal) {

    m_quaternion *= glm::angleAxis(radians, axisNormal);
    return *this;

}

tw::Rotation& tw::Rotation::rotateByDegrees (float degrees, const Vector3& axisNormal) {

    m_quaternion *= glm::angleAxis(glm::radians(degrees), axisNormal);
    return *this;

}

tw::Rotation& tw::Rotation::rotateTo (const Rotation& rotation) {

    m_quaternion = rotation.getQuaternion();
    return *this;

}

tw::Rotation& tw::Rotation::rotateToRadians (float radians, const Vector3& axisNormal) {

    reset().rotateByRadians(radians, axisNormal);
    return *this;

}

tw::Rotation& tw::Rotation::rotateToDegrees (float degrees, const Vector3& axisNormal) {

    reset().rotateByDegrees(degrees, axisNormal);
    return *this;

}

tw::Rotation& tw::Rotation::reset () {

    m_quaternion = {};
    return *this;

}

tw::Rotation::operator tw::Quaternion () const {

    return getQuaternion();

}

tw::Rotation tw::Rotation::operator * (float right) const {

    return m_quaternion * right;

}

tw::Rotation& tw::Rotation::operator *= (float right) {

    m_quaternion *= right;
    return *this;

}
