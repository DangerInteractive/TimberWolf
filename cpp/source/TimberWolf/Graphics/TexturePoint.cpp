#include "../../../include/TimberWolf/Graphics/TexturePoint.hpp"

/**
 * Constructor taking in normalized texture U and V coordinates.
 *
 * @param u normalized texture U coordinate (0-1)
 * @param v normalized texture V coordinate (0-1)
 */
tw::TexturePoint::TexturePoint (float u, float v)
: m_u(std::clamp(u, 0.f, 1.f)), m_v(std::clamp(v, 0.f, 1.f)) {}

/**
 * Get the normalized texture coordinate U.
 *
 * @return normalized texture coordinate u
 */
float tw::TexturePoint::getU () const {

    return m_u;

}

/**
 * Get the normalized texture coordinate V.
 *
 * @return normalized texture coordinate v
 */
float tw::TexturePoint::getV () const {

    return m_v;

}

/**
 * Set the normalized texture coordinate U. Note that the value will be clamped.
 *
 * @param u new normalized texture coordinate u
 */
void tw::TexturePoint::setU (float u) {

    m_u = std::clamp(u, 0.f, 1.f);

}

/**
 * Set the normalized texture coordinate V. Note that the value will be clamped.
 *
 * @param v new normalized texture coordinate v
 */
void tw::TexturePoint::setV (float v) {

    m_v = std::clamp(v, 0.f, 1.f);

}
