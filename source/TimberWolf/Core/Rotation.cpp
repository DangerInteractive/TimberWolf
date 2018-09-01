#include "../../../include/TimberWolf/Core/Rotation.hpp"

tw::Rotation::Rotation (Quaternion&& quat) {

    *this = static_cast<Rotation>(std::move(quat));

}

tw::Rotation::Rotation (const Quaternion& quat) {

    *this = static_cast<Rotation>(quat);

}

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

void tw::Rotation::rotateBy (const Rotation& rotation) {

    *this *= static_cast<Quaternion>(rotation);

}

void tw::Rotation::rotateByRadians (float radians, const Vector3& axisNormal) {

    *this *= glm::angleAxis(radians, axisNormal);

}

void tw::Rotation::rotateByDegrees (float degrees, const Vector3& axisNormal) {

    *this *= glm::angleAxis(glm::radians(degrees), axisNormal);

}

void tw::Rotation::rotateTo (const Rotation& rotation) {

    *this = rotation;

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

    *this = {};

}
