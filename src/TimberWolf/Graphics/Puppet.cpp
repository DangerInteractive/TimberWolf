#include "../../../include/TimberWolf/Graphics/Puppet.hpp"

const tw::Vertex& tw::Puppet::getPosition () const {

    return m_position;

}

float tw::Puppet::getPositionX () const {

    return m_position.getX();

}

float tw::Puppet::getPositionY () const {

    return m_position.getY();

}

float tw::Puppet::getPositionZ () const {

    return m_position.getZ();

}

const tw::Vertex& tw::Puppet::getHandle () const {

    return m_handle;

}

float tw::Puppet::getHandleX () const {

    return m_handle.getX();

}

float tw::Puppet::getHandleY () const {

    return m_handle.getY();

}

float tw::Puppet::getHandleZ () const {

    return m_handle.getZ();

}

const tw::Rotation& tw::Puppet::getOrientation () const {

    return m_orientation;

}

tw::Puppet& tw::Puppet::translateBy (const Vertex& vertex) {

    m_position += vertex;
    return *this;

}

tw::Puppet& tw::Puppet::translateBy (float x, float y, float z) {

    m_position += Vertex(x, y, z);
    return *this;

}

tw::Puppet& tw::Puppet::translateXBy (float x) {

    return translateBy(x, 0.f, 0.f);

}

tw::Puppet& tw::Puppet::translateYBy (float y) {

    return translateBy(0.f, y, 0.f);

}

tw::Puppet& tw::Puppet::translateZBy (float z) {

    return translateBy(0.f, 0.f, z);

}

tw::Puppet& tw::Puppet::translateTo (const Vertex& vertex) {

    m_position = vertex;
    return *this;

}

tw::Puppet& tw::Puppet::translateTo (float x, float y, float z) {

    m_position = Vertex(x, y, z);
    return *this;

}

tw::Puppet& tw::Puppet::translateXTo (float x) {

    m_position.setX(x);
    return *this;

}

tw::Puppet& tw::Puppet::translateYTo (float y) {

    m_position.setY(y);
    return *this;

}

tw::Puppet& tw::Puppet::translateZTo (float z) {

    m_position.setZ(z);
    return *this;

}

tw::Puppet& tw::Puppet::moveHandleBy (const Vertex& vertex) {

    m_handle += vertex;
    return *this;

}

tw::Puppet& tw::Puppet::moveHandleBy (float x, float y, float z) {

    m_handle += Vertex(x, y, z);
    return *this;

}

tw::Puppet& tw::Puppet::moveHandleXBy (float x) {

    return moveHandleBy(x, 0.f, 0.f);

}

tw::Puppet& tw::Puppet::moveHandleYBy (float y) {

    return moveHandleBy(0.f, y, 0.f);

}

tw::Puppet& tw::Puppet::moveHandleZBy (float z) {

    return moveHandleBy(0.f, 0.f, z);

}

tw::Puppet& tw::Puppet::moveHandleTo (const Vertex& vertex) {

    m_handle = vertex;
    return *this;

}

tw::Puppet& tw::Puppet::moveHandleTo (float x, float y, float z) {

    m_handle = Vertex(x, y, z);
    return *this;

}

tw::Puppet& tw::Puppet::moveHandleXTo (float x) {

    m_handle.setX(x);
    return *this;

}

tw::Puppet& tw::Puppet::moveHandleYTo (float y) {

    m_handle.setY(y);
    return *this;

}

tw::Puppet& tw::Puppet::moveHandleZTo (float z) {

    m_handle.setZ(z);
    return *this;

}

tw::Puppet& tw::Puppet::rotateByRadians (float radians, const Vertex& axisNormal) {

    m_orientation.rotateByRadians(radians, axisNormal);
    return *this;

}

tw::Puppet& tw::Puppet::rotateByDegrees (float degrees, const Vertex& axisNormal) {

    m_orientation.rotateByDegrees(degrees, axisNormal);
    return *this;

}

tw::Puppet& tw::Puppet::rotateToRadians (float radians, const Vertex& axisNormal) {

    m_orientation.rotateToRadians(radians, axisNormal);
    return *this;

}

tw::Puppet& tw::Puppet::rotateToDegrees (float degrees, const Vertex& axisNormal) {

    m_orientation.rotateToDegrees(degrees, axisNormal);
    return *this;

}
