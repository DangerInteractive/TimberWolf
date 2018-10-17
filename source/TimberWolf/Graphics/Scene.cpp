#include "../../../include/TimberWolf/Graphics/Scene.hpp"

/**
 * @class tw::Scene
 *
 * Representation of a scene, containing entities, actors, etc. This class is
 * not complete yet.
 */

unsigned int tw::Scene::getModelCount () const {

    return m_models.size();

}

std::vector<tw::Model>& tw::Scene::getModels () {

    return m_models;

}

tw::Model& tw::Scene::getModel (unsigned int index) {

    return m_models.at(index);

}

void tw::Scene::addModels (const Model& models...) {

    m_models.emplace_back(models);

}

void tw::Scene::setModel (unsigned int index, const Model& model) {

    m_models.at(index) = model;

}

void tw::Scene::clearModels () {

    m_models.clear();

}
