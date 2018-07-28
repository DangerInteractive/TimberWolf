#include "../../../include/TimberWolf/World/Entity.hpp"

void tw::Entity::update (double deltaTime) {}

tw::Vertex tw::Entity::getPosition () const {

    return m_position;

}

const tw::Vertex& tw::Entity::getPositionRef () const {

    return m_position;

}

float tw::Entity::getPositionX () const {

    return m_position.x;

}

float tw::Entity::getPositionY () const {

    return m_position.y;

}

float tw::Entity::getPositionZ () const {

    return m_position.z;

}

tw::Rotation tw::Entity::getOrientation () const {

    return m_orientation;

}

const tw::Rotation& tw::Entity::getOrientationRef () const {

    return m_orientation;

}

tw::Vertex tw::Entity::getScale () const {

    return m_scale;

}

const tw::Vertex& tw::Entity::getScaleRef () const {

    return m_scale;

}

float tw::Entity::getScaleX () const {

    return m_scale.x;

}

float tw::Entity::getScaleY () const {

    return m_scale.y;

}

float tw::Entity::getScaleZ () const {

    return m_scale.z;

}
