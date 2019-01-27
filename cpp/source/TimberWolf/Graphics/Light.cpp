#include "../../../include/TimberWolf/Graphics/Light.hpp"

#include <algorithm>

#include "../../../include/TimberWolf/Core/Math.hpp"

tw::Color tw::Light::getColor () const noexcept {

    return m_color;

}

float tw::Light::getColorR () const noexcept {

    return m_color.getR();

}

float tw::Light::getColorG () const noexcept {

    return m_color.getG();

}

float tw::Light::getColorB () const noexcept {

    return m_color.getB();

}

float tw::Light::getColorA () const noexcept {

    return m_color.getA();

}

void tw::Light::setColor (Color color) noexcept {

    m_color = color;

}

void tw::Light::setColor (float r, float g, float b, float a) noexcept {

    m_color = Color(r, g, b, a);

}

void tw::Light::setColorR (float r) noexcept {

    m_color.setR(r);

}

void tw::Light::setColorG (float g) noexcept {

    m_color.setG(g);

}

void tw::Light::setColorB (float b) noexcept {

    m_color.setB(b);

}

void tw::Light::setColorA (float a) noexcept {

    m_color.setA(a);

}

float tw::Light::getIntensity () const noexcept {

    return m_intensity;

}

void tw::Light::setIntensity (float intensity) noexcept {

    m_intensity = std::clamp(intensity, 0.f, std::numeric_limits<float>::infinity());

}

bool tw::Light::positionEnabled () const noexcept {

    return m_hasPosition;

}

void tw::Light::enablePosition () noexcept {

    m_hasPosition = true;

}

void tw::Light::disablePosition () noexcept {

    m_hasPosition = false;

}

tw::Vertex tw::Light::getPosition () const noexcept {

    return m_position;

}

float tw::Light::getPositionX () const noexcept {

    return m_position.x;

}

float tw::Light::getPositionY () const noexcept {

    return m_position.y;

}

float tw::Light::getPositionZ () const noexcept {

    return m_position.z;

}

void tw::Light::setPosition (Vertex position) noexcept {

    m_position = position;

}

void tw::Light::setPosition (float x, float y, float z) noexcept {

    m_position = Vertex(x, y, z);

}

void tw::Light::setPositionX (float x) noexcept {

    m_position.x = x;

}

void tw::Light::setPositionY (float y) noexcept {

    m_position.y = y;

}

void tw::Light::setPositionZ (float z) noexcept {

    m_position.z = z;

}

bool tw::Light::directionEnabled () const noexcept {

    return m_hasDirection;

}

void tw::Light::enableDirection () noexcept {

    m_hasDirection = true;

}

void tw::Light::disableDirection () noexcept {

    m_hasDirection = false;

}

tw::Normal tw::Light::getDirection () const noexcept {

    return m_direction;

}

float tw::Light::getDirectionX () const noexcept {

    return m_direction.x;

}

float tw::Light::getDirectionY () const noexcept {

    return m_direction.y;

}

float tw::Light::getDirectionZ () const noexcept {

    return m_direction.z;

}

void tw::Light::setDirection (Normal direction) noexcept {

    m_direction = direction;

}

void tw::Light::setDirection (float x, float y, float z) noexcept {

    m_direction = Normal(x, y, z);

}

void tw::Light::setDirectionX (float x) noexcept {

    m_direction.x = x;

}

void tw::Light::setDirectionY (float y) noexcept {

    m_direction.y = y;

}

void tw::Light::setDirectionZ (float z) noexcept {

    m_direction.z = z;

}

bool tw::Light::spreadEnabled () const noexcept {

    return m_hasSpread;

}

void tw::Light::enableSpread () noexcept {

    m_hasSpread = true;

}

void tw::Light::disableSpread () noexcept {

    m_hasSpread = false;

}

float tw::Light::getSpreadRadians () const noexcept {

    return m_spreadRadians;

}

float tw::Light::getSpreadDegrees () const noexcept {

    return Math::radiansToDegrees(m_spreadRadians);

}

void tw::Light::setSpreadRadians (float radians) noexcept {

    m_spreadRadians = radians;

}

void tw::Light::setSpreadDegrees (float degrees) noexcept {

    m_spreadRadians = Math::degreesToRadians(degrees);

}
