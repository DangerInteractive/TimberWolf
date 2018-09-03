#include "../../../include/TimberWolf/Graphics/Scene.hpp"

/**
 * @class tw::Scene
 *
 * Representation of a scene, containing entities, actors, etc. This class is
 * not complete yet.
 */

unsigned int tw::Scene::getPuppetCount () const {

    return m_puppets.size();

}

const std::vector<std::shared_ptr<tw::Puppet>>& tw::Scene::getPuppets () const {

    return m_puppets;

}

tw::Puppet* tw::Scene::getPuppet (unsigned int index) const {

    return m_puppets.at(index).get();

}

void tw::Scene::addPuppets (std::shared_ptr<Puppet> puppets...) {

    m_puppets.emplace_back(puppets);

}

void tw::Scene::setPuppet (unsigned int index, std::shared_ptr<Puppet> puppet) {

    m_puppets.at(index) = puppet;

}

void tw::Scene::clearPuppets () {

    m_puppets.clear();

}
