#include "../../../include/TimberWolf/Graphics/ModelFragment.hpp"

tw::Mesh* tw::ModelFragment::getMesh () const {

    return m_mesh.get();

}

void tw::ModelFragment::setMesh (const std::shared_ptr<Mesh>& mesh) {

    m_mesh = mesh;

}

tw::Material* tw::ModelFragment::getMaterial () const {

    return m_material.get();

}

void tw::ModelFragment::setMaterial (const std::shared_ptr<Material>& material) {

    m_material = material;

}

const tw::Transformation& tw::ModelFragment::getTransformation () const {

    return m_transformation;

}

void tw::ModelFragment::setTransformation (Transformation&& transformation) {

    m_transformation = std::move(transformation);

}

void tw::ModelFragment::setTransformation (const Transformation& transformation) {

    m_transformation = transformation;

}
