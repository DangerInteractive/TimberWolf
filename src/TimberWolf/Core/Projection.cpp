#include "../../../include/TimberWolf/Core/Projection.hpp"

tw::Projection::Builder& tw::Projection::Builder::setFieldOfViewRadians (float radians) {

    m_fovDegrees = glm::degrees(radians);
    return *this;

}

tw::Projection::Builder& tw::Projection::Builder::setFieldOfViewDegrees (float degrees) {

    m_fovDegrees = degrees;
    return *this;

}

tw::Projection::Builder& tw::Projection::Builder::setAspectRatio (float aspectRatio) {

    m_aspectRatio = aspectRatio;
    return *this;

}

tw::Projection::Builder& tw::Projection::Builder::setNearPlane (float distance) {

    m_nearPlane = distance;
    return *this;

}

tw::Projection::Builder& tw::Projection::Builder::setFarPlane (float distance) {

    m_farPlane = distance;
    return *this;

}

tw::Projection&& tw::Projection::Builder::build () && {

    auto proj = Projection(std::move(m_fovDegrees), std::move(m_aspectRatio), std::move(m_nearPlane), std::move(m_farPlane));
    return std::move(proj);

}

tw::Projection tw::Projection::Builder::build () & {

    return Projection(m_fovDegrees, m_aspectRatio, m_nearPlane, m_farPlane);

}

tw::Projection::Projection (float fovDegrees, float aspectRatio, float nearPlane, float farPlane) {

    *this = glm::perspective(fovDegrees, aspectRatio, nearPlane, farPlane);

}
