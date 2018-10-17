#include "../../../include/TimberWolf/Graphics/Model.hpp"

/**
 * @class tw::Model
 *
 * A representation of a 3D object to be rendered within a scene. It contains
 * shared pointers to a mesh, a material that should be applied to the mesh, and
 * a transformation relative to the scene in which it resides.
 */

tw::Mesh* tw::Model::getMesh () noexcept {

    return m_mesh.get();

}

const tw::Mesh* tw::Model::getMesh () const noexcept {

    return m_mesh.get();

}

std::shared_ptr<tw::Mesh> tw::Model::getMeshShared () noexcept {

    return m_mesh;

}

void tw::Model::setMesh (const std::shared_ptr<Mesh>& mesh) {

    m_mesh = mesh;

}

void tw::Model::setMesh (Mesh* mesh) {

    m_mesh = std::shared_ptr<Mesh>(mesh);

}

tw::Material* tw::Model::getMaterial () noexcept {

    return m_material.get();

}

const tw::Material* tw::Model::getMaterial () const noexcept {

    return m_material.get();

}

std::shared_ptr<tw::Material> tw::Model::getMaterialShared () noexcept {

    return m_material;

}

const std::shared_ptr<tw::Material> tw::Model::getMaterialShared () const noexcept {

    return m_material;

}

const tw::Vector3& tw::Model::getScale () const noexcept {

    return m_scale;

}

const tw::Rotation& tw::Model::getRotation () const noexcept {

    return m_rotation;

}

const tw::Vertex& tw::Model::getTranslation () const noexcept {

    return m_translation;

}

const tw::Transformation& tw::Model::getTransform () noexcept {

    if (m_dirtyTransform) {
        calculateTransform();
    }

    return m_transform;

}

void tw::Model::setTransform (const Vector3& scale, const Rotation& rotation, const Vertex& translation) {

    m_scale = scale;
    m_rotation = rotation;
    m_translation = translation;

    m_dirtyTransform = true;

}

void tw::Model::setTranslation (const Vertex& translation) {

    m_translation = translation;
    m_dirtyTransform = true;

}

void tw::Model::setTranslation (float x, float y, float z) {

    m_translation = {x, y, z};
    m_dirtyTransform = true;

}

void tw::Model::setRotation (const Rotation& rotation) {

    m_rotation = rotation;
    m_dirtyTransform = true;

}

void tw::Model::setRotationRadians (float radians, const Normal& axis) {

    m_rotation = Rotation::fromRadians(radians, axis);
    m_dirtyTransform = true;

}

void tw::Model::setRotationDegrees (float degrees, const Normal& axis) {

    m_rotation = Rotation::fromDegrees(degrees, axis);
    m_dirtyTransform = true;

}

void tw::Model::setScale (float scale) {

    m_scale = {scale, scale, scale};
    m_dirtyTransform = true;

}

void tw::Model::setScale (const Vector3& scale) {

    m_scale = scale;
    m_dirtyTransform = true;

}

void tw::Model::setScale (float x, float y, float z) {

    m_scale = {x, y, z};
    m_dirtyTransform = true;

}

void tw::Model::calculateTransform () noexcept {

    m_transform = Transformation::Builder()
        .setScale(m_scale)
        .setRotation(m_rotation)
        .setTranslation(m_translation)
        .build();

    m_dirtyTransform = false;

}
