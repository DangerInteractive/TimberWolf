#include "../../../include/TimberWolf/World/Entity.hpp"

void tw::Entity::update (double deltaTime) {}

tw::Vertex tw::Entity::getPosition () const {

    return m_position;

}

const tw::Vertex& tw::Entity::getPositionRef () const {

    return m_position;

}

float tw::Entity::getPositionX () const {

    return m_position.x;

}

float tw::Entity::getPositionY () const {

    return m_position.y;

}

float tw::Entity::getPositionZ () const {

    return m_position.z;

}

void tw::Entity::translate (const Vertex& vector) {

    m_position += vector;

}

void tw::Entity::translate (float x, float y, float z) {

    m_position.x += x;
    m_position.y += y;
    m_position.z += z;

}

void tw::Entity::translateX (float x) {

    m_position.x += x;

}

void tw::Entity::translateY (float y) {

    m_position.y += y;

}

void tw::Entity::translateZ (float z) {

    m_position.z += z;

}

tw::Rotation tw::Entity::getOrientation () const {

    return m_orientation;

}

const tw::Rotation& tw::Entity::getOrientationRef () const {

    return m_orientation;

}

void tw::Entity::setOrientation (const Rotation& orientation) {

    m_orientation = orientation;

}

void tw::Entity::setOrientationRadians (float radians, const Vertex& axis) {

    m_orientation = Rotation::fromRadians(radians, axis);

}

void tw::Entity::setOrientationDegrees (float degrees, const Vertex& axis) {

    m_orientation = Rotation::fromDegrees(degrees, axis);

}

void tw::Entity::rotate (const Rotation& rotation) {

    m_orientation.rotateBy(rotation);

}

void tw::Entity::rotateRadians (float radians, const Vertex& axis) {

    m_orientation.rotateByRadians(radians, axis);

}

void tw::Entity::rotateDegrees (float degrees, const Vertex& axis) {

    m_orientation.rotateByDegrees(degrees, axis);

}

tw::Vertex tw::Entity::getScale () const {

    return m_scale;

}

const tw::Vertex& tw::Entity::getScaleRef () const {

    return m_scale;

}

float tw::Entity::getScaleX () const {

    return m_scale.x;

}

float tw::Entity::getScaleY () const {

    return m_scale.y;

}

float tw::Entity::getScaleZ () const {

    return m_scale.z;

}

void tw::Entity::setScale (const Vertex& vector) {

    m_scale = vector;

}

void tw::Entity::setScale (float x, float y, float z) {

    m_scale = Vector3(x, y, z);

}

void tw::Entity::setScale (float scale) {

    m_scale = Vector3(scale, scale, scale);

}

void tw::Entity::setScaleX (float x) {

    m_scale.x = x;

}

void tw::Entity::setScaleY (float y) {

    m_scale.y = y;

}

void tw::Entity::setScaleZ (float z) {

    m_scale.z = z;

}

void tw::Entity::scale (const Vertex& vector) {

    m_scale *= vector;

}

void tw::Entity::scale (float x, float y, float z) {

    m_scale.x *= x;
    m_scale.y *= y;
    m_scale.z *= z;

}

void tw::Entity::scale (float scale) {

    m_scale.x *= scale;
    m_scale.y *= scale;
    m_scale.z *= scale;

}

void tw::Entity::scaleX (float x) {

    m_scale.x *= x;

}

void tw::Entity::scaleY (float y) {

    m_scale.y *= y;

}

void tw::Entity::scaleZ (float z) {

    m_scale.z *= z;

}
