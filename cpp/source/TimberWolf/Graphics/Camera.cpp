#include "../../../include/TimberWolf/Graphics/Camera.hpp"

tw::Matrix4 tw::Camera::getViewProjection () {

    calculateViewProjectionMatrix();
    return m_viewProjection;

}

const tw::Matrix4& tw::Camera::getViewProjectionRef () {

    calculateViewProjectionMatrix();
    return m_viewProjection;

}

tw::Transformation tw::Camera::getView () {

    calculateViewMatrix();
    return m_view;

}

const tw::Transformation& tw::Camera::getViewRef () {

    calculateViewMatrix();
    return m_view;

}

tw::Projection tw::Camera::getProjection () {

    calculateProjectionMatrix();
    return m_projection;

}

const tw::Projection& tw::Camera::getProjectionRef () {

    calculateProjectionMatrix();
    return m_projection;

}

void tw::Camera::placeInScene (Scene* scene) {

    m_scene = scene;

}

void tw::Camera::removeFromScene () {

    m_scene = nullptr;

}

void tw::Camera::setPosition (const Vertex& position) {

    m_position = position;
    m_dirtyView = true;

}

void tw::Camera::setPosition (float x, float y, float z) {

    m_position = {x, y, z};
    m_dirtyView = true;

}

void tw::Camera::setPositionX (float x) {

    m_position.x = x;
    m_dirtyView = true;

}

void tw::Camera::setPositionY (float y) {

    m_position.y = y;
    m_dirtyView = true;

}

void tw::Camera::setPositionZ (float z) {

    m_position.z = z;
    m_dirtyView = true;

}

void tw::Camera::setOrientation (const Rotation& orientation) {

    m_orientation = orientation;
    m_dirtyView = true;

}

void tw::Camera::setOrientationRadians (float radians, const Vector3& angleAxis) {

    m_orientation = Rotation::fromRadians(radians, angleAxis);
    m_dirtyView = true;

}

void tw::Camera::setOrientationDegrees (float degrees, const Vector3& angleAxis) {

    m_orientation = Rotation::fromDegrees(degrees, angleAxis);
    m_dirtyView = true;

}

void tw::Camera::setFieldOfViewRadians (float radians) {

    m_fovDegrees = Math::radiansToDegrees(radians);
    m_dirtyProjection = true;

}

void tw::Camera::setFieldOfViewDegrees (float degrees) {

    m_fovDegrees = degrees;
    m_dirtyProjection = true;

}

void tw::Camera::setAspectRatio (float aspectRatio) {

    m_aspectRatio = aspectRatio;
    m_dirtyProjection = true;

}

void tw::Camera::setDimensions (unsigned int width, unsigned int height) {

    m_aspectRatio = static_cast<float>(
        (static_cast<double>(width)) /
        (static_cast<double>(height))
    );
    m_dirtyProjection = true;

}

void tw::Camera::setFrontPlane (float distance) {

    m_frontPlane = distance;
    m_dirtyProjection = true;

}

void tw::Camera::setBackPlane (float distance) {

    m_backPlane = distance;
    m_dirtyProjection = true;

}

void tw::Camera::calculateViewMatrix () {

    if (m_dirtyView) {
        m_view = Transformation(1.f, m_orientation, m_position);
        m_dirtyView = false;
    }

}

void tw::Camera::calculateProjectionMatrix () {

    if (m_dirtyProjection) {
        m_projection = Projection(m_fovDegrees, m_aspectRatio, m_frontPlane, m_backPlane);
        m_dirtyProjection = false;
    }

}

void tw::Camera::calculateViewProjectionMatrix () {

    calculateViewMatrix();
    calculateProjectionMatrix();

}
