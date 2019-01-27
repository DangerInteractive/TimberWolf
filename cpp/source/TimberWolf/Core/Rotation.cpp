#include "../../../include/TimberWolf/Core/Rotation.hpp"

tw::Rotation::Rotation (Quaternion&& quat)
: m_quat(std::move(quat)) {}

tw::Rotation::Rotation (const Quaternion& quat)
: m_quat(quat) {}

tw::Rotation tw::Rotation::fromRadians (float radians, const Vector3& angleAxis) {

    auto rot = Rotation();
    rot.rotateByRadians(std::move(radians), std::move(angleAxis));
    return rot;

}

tw::Rotation tw::Rotation::fromDegrees (float degrees, const Vector3& angleAxis) {

    auto rot = Rotation();
    rot.rotateByDegrees(std::move(degrees), std::move(angleAxis));
    return rot;

}

const tw::Quaternion& tw::Rotation::getQuaternion () const {

    return m_quat;

}

void tw::Rotation::rotateBy (const Rotation& rotation) {

    m_quat = normalize(m_quat * rotation.getQuaternion());

}

void tw::Rotation::rotateByRadians (float radians, const Vector3& axisNormal) {

    m_quat = normalize(m_quat * glm::angleAxis(radians, axisNormal));

}

void tw::Rotation::rotateByDegrees (float degrees, const Vector3& axisNormal) {

    m_quat = normalize(m_quat * glm::angleAxis(glm::radians(degrees), axisNormal));

}

void tw::Rotation::rotateTo (const Rotation& rotation) {

    m_quat = rotation.getQuaternion();

}

void tw::Rotation::rotateToRadians (float radians, const Vector3& axisNormal) {

    reset();
    rotateByRadians(radians, axisNormal);

}

void tw::Rotation::rotateToDegrees (float degrees, const Vector3& axisNormal) {

    reset();
    rotateByDegrees(degrees, axisNormal);

}

void tw::Rotation::reset () {

    m_quat = {};

}

tw::Rotation::operator Quaternion () {

    return m_quat;

}

tw::Quaternion tw::Rotation::normalize (Quaternion quat) {

    return glm::normalize(quat);

}
