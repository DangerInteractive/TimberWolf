#include "../../../include/TimberWolf/Core/Transformation.hpp"

tw::Transformation::Builder& tw::Transformation::Builder::setScale (float scale) {

    m_scale = {scale, scale, scale};
    return *this;

}

tw::Transformation::Builder& tw::Transformation::Builder::setScale (const Vector3& scale) {

    m_scale = scale;
    return *this;

}

tw::Transformation::Builder& tw::Transformation::Builder::setScale (float x, float y, float z) {

    m_scale = {x, y, z};
    return *this;

}

tw::Transformation::Builder& tw::Transformation::Builder::setScaleX (float x) {

    m_scale.x = x;
    return *this;

}

tw::Transformation::Builder& tw::Transformation::Builder::setScaleY (float y) {

    m_scale.y = y;
    return *this;

}

tw::Transformation::Builder& tw::Transformation::Builder::setScaleZ (float z) {

    m_scale.z = z;
    return *this;

}

tw::Transformation::Builder& tw::Transformation::Builder::setRotation (const Rotation& rotation) {

    m_rotation = rotation;
    return *this;

}

tw::Transformation::Builder& tw::Transformation::Builder::setRotationRadians (float radians, const Vector3& angleAxis) {

    m_rotation = Rotation::fromRadians(radians, angleAxis);
    return *this;

}

tw::Transformation::Builder& tw::Transformation::Builder::setRotationDegrees (float degrees, const Vector3& angleAxis) {

    m_rotation = Rotation::fromDegrees(degrees, angleAxis);
    return *this;

}

tw::Transformation::Builder& tw::Transformation::Builder::setTranslation (const Vector3& translation) {

    m_translation = translation;
    return *this;

}

tw::Transformation::Builder& tw::Transformation::Builder::setTranslation (float x, float y, float z) {

    m_translation = {x, y, z};
    return *this;

}

tw::Transformation::Builder& tw::Transformation::Builder::setTranslationX (float x) {

    m_translation.x = x;
    return *this;

}

tw::Transformation::Builder& tw::Transformation::Builder::setTranslationY (float y) {

    m_translation.y = y;
    return *this;

}

tw::Transformation::Builder& tw::Transformation::Builder::setTranslationZ (float z) {

    m_translation.z = z;
    return *this;

}

tw::Transformation tw::Transformation::Builder::build () {

    return Transformation(m_scale, m_rotation, m_translation);

}

tw::Transformation::Transformation (Matrix4&& from)
: Matrix4(std::move(from)) {}

tw::Transformation::Transformation (const Matrix4& from)
: Matrix4(from) {}

tw::Transformation::Transformation (float scale, const Rotation& rotation, const Vector3& translation) {

    *this = glm::scale(*this, {scale, scale, scale});
    *this *= glm::mat4_cast(rotation);
    *this = glm::translate(*this, translation);

}

tw::Transformation::Transformation (const Vector3& scale, const Rotation& rotation, const Vector3& translation) {

    *this = glm::scale(*this, scale);
    *this *= glm::mat4_cast(rotation);
    *this = glm::translate(*this, translation);

}
