#include "../../../include/TimberWolf/Graphics/Puppet.hpp"

tw::Model* tw::Puppet::getModel () {

    return m_model.get();

}

std::shared_ptr<tw::Model> tw::Puppet::getModelShared () {

    return m_model;

}

void tw::Puppet::setModel (const std::shared_ptr<Model>& model) {

    m_model = model;

}

tw::Material* tw::Puppet::getMaterial () {

    return m_material.get();

}

std::shared_ptr<tw::Material> tw::Puppet::getMaterialShared () {

    return m_material;

}

void tw::Puppet::setMaterial (const std::shared_ptr<Material>& material) {

    m_material = material;

}
