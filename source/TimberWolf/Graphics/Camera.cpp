#include "../../../include/TimberWolf/Graphics/Camera.hpp"

tw::Matrix4 tw::Camera::getViewProjection () const {

    return m_viewProjection;

}

const tw::Matrix4& tw::Camera::getViewProjectionRef () const {

    return m_viewProjection;

}

tw::Transformation tw::Camera::getView () const {

    return m_view;

}

const tw::Transformation& tw::Camera::getViewRef () const {

    return m_view;

}

tw::Projection tw::Camera::getProjection () const {

    return m_projection;

}

const tw::Projection& tw::Camera::getProjectionRef () const {

    return m_projection;

}

tw::Camera& tw::Camera::setPosition (const Vertex& position) {

    m_position = position;
    m_dirtyView = true;

    return *this;

}

tw::Camera& tw::Camera::setPosition (float x, float y, float z) {

    m_position = {x, y, z};
    m_dirtyView = true;

    return *this;

}

tw::Camera& tw::Camera::setPositionX (float x) {

    m_position.x = x;
    m_dirtyView = true;

    return *this;

}

tw::Camera& tw::Camera::setPositionY (float y) {

    m_position.y = y;
    m_dirtyView = true;

    return *this;

}

tw::Camera& tw::Camera::setPositionZ (float z) {

    m_position.z = z;
    m_dirtyView = true;

    return *this;

}

tw::Camera& tw::Camera::setOrientation (const Rotation& orientation) {

    m_orientation = orientation;
    m_dirtyView = true;

    return *this;

}

tw::Camera& tw::Camera::setOrientationRadians (float radians, const Vector3& angleAxis) {

    m_orientation = Rotation::fromRadians(radians, angleAxis);
    m_dirtyView = true;

    return *this;

}

tw::Camera& tw::Camera::setOrientationDegrees (float degrees, const Vector3& angleAxis) {

    m_orientation = Rotation::fromDegrees(degrees, angleAxis);
    m_dirtyView = true;

    return *this;

}

tw::Camera& tw::Camera::setFieldOfViewRadians (float radians) {

    m_fovDegrees = Math::radiansToDegrees(radians);
    m_dirtyProjection = true;

    return *this;

}

tw::Camera& tw::Camera::setFieldOfViewDegrees (float degrees) {

    m_fovDegrees = degrees;
    m_dirtyProjection = true;

    return *this;

}

tw::Camera& tw::Camera::setAspectRatio (float aspectRatio) {

    m_aspectRatio = aspectRatio;
    m_dirtyProjection = true;

    return *this;

}

tw::Camera& tw::Camera::setDimensions (unsigned int width, unsigned int height) {

    m_aspectRatio = static_cast<float>(
        (static_cast<double>(width)) /
        (static_cast<double>(height))
    );
    m_dirtyProjection = true;

    return *this;

}

tw::Camera& tw::Camera::setFrontPlane (float distance) {

    m_frontPlane = distance;
    m_dirtyProjection = true;

    return *this;

}

tw::Camera& tw::Camera::setBackPlane (float distance) {

    m_backPlane = distance;
    m_dirtyProjection = true;

    return *this;

}

void tw::Camera::commit () {

    if (m_dirtyView) {
        m_view = Transformation(1.f, m_orientation, m_position);
        m_dirtyView = false;
    }

    if (m_dirtyProjection) {
        m_projection = Projection(m_fovDegrees, m_aspectRatio, m_frontPlane, m_backPlane);
        m_dirtyProjection = false;
    }

}
