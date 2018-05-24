#include "../include/TexturePoint.hpp"

/**
 * Constructor taking in normalized texture U and V coordinates.
 *
 * @param u normalized texture U coordinate (0-1)
 * @param v normalized texture V coordinate (0-1)
 */
tw::TexturePoint::TexturePoint (float u, float v)
: m_u(clamp(u)), m_v(clamp(v)) {}

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

    m_u = clamp(u);

}

/**
 * Set the normalized texture coordinate V. Note that the value will be clamped.
 *
 * @param v new normalized texture coordinate v
 */
void tw::TexturePoint::setV (float v) {

    m_v = clamp(v);

}

/**
 * Clamp a normalized value between 0 and 1.
 *
 * @param value value to clamp
 * @return value clamped between 0 and 1
 */
float tw::TexturePoint::clamp (float value) {

    return std::clamp(value, 0.f, 1.f);

}
