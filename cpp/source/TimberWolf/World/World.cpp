#include "../../../include/TimberWolf/World/World.hpp"

void tw::World::update (double deltaTime) {

    preUpdate();

    for (unsigned int i = 0; i < m_entities.size(); ++i) {
        m_entities.at(i)->update(deltaTime);
    }

    postUpdate();

}

tw::World& tw::World::addEntity (std::unique_ptr<Entity>&& entity) {

    m_entities.emplace_back(std::move(entity));
    return *this;

}

tw::World& tw::World::addEntity (Entity* entity) {

    m_entities.emplace_back(entity);
    return *this;

}

void tw::World::preUpdate () {

    m_running = true;

}

void tw::World::postUpdate () {

    m_running = false;

    m_entities.insert(
        m_entities.end(),
        std::make_move_iterator(m_pendingEntities.begin()),
        std::make_move_iterator(m_pendingEntities.end())
    );
    m_pendingEntities.clear();

}
