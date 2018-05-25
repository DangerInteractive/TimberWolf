#include "../../../include/TimberWolf/Core/Color.hpp"

/**
 * @class tw::Color
 *
 * Class for representing an RGBA color.
 */

/**
 * Color constructor, taking in normalized values of the red, green, blue, and alpha channels.
 *
 * @param r normalized (0-1) red channel value
 * @param g normalized (0-1) green channel value
 * @param b normalized (0-1) blue channel value
 * @param a normalized (0-1) alpha channel value
 */
tw::Color::Color (float r, float g, float b, float a) {

    setRGBA(r, g, b, a);

}

/**
 * Get a tuple of the normalized values of the red, green, blue, and alpha channels.
 *
 * @return a 4-element tuple containing the normalized (0-1) values of the red, green, blue, and alpha channels, in that order
 */
std::tuple<float, float, float, float> tw::Color::getRGBA () const {

    return std::make_tuple<float, float, float, float>(
        getR(), getG(), getB(), getA()
    );

}

/**
 * Get a tuple of the 8-bit integral values of the red, green, blue, and alpha channels.
 *
 * @return a 4-element tuple containing the 8-bit integral (0-255) values of the red, green, blue, and alpha channels, in that order
 */
std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> tw::Color::getRGBA8 () const {

    return std::make_tuple<uint8_t, uint8_t, uint8_t, uint8_t>(
        getR8(), getG8(), getB8(), getA8()
    );

}

/**
 * Get a tuple of the 16-bit integral values of the red, green, blue, and alpha channels.
 *
 * @return a 4-element tuple containing the 16-bit integral (0-65535) values of the red, green, blue, and alpha channels, in that order
 */
std::tuple<uint16_t, uint16_t, uint16_t, uint16_t> tw::Color::getRGBA16 () const {

    return std::make_tuple<uint16_t, uint16_t, uint16_t, uint16_t>(
        getR16(), getG16(), getB16(), getA16()
    );

}

/**
 * Get the normalized value of the red channel.
 *
 * @return the normalized (0-1) value of the red channel
 */
float tw::Color::getR () const {

    return m_r;

}

/**
 * Get the 8-bit integral value of the red channel.
 *
 * @return the 8-bit integral (0-255) value of the red channel
 */
uint8_t tw::Color::getR8 () const {

    return static_cast<uint8_t>(m_r * 255.f);

}

/**
 * Get the 16-bit integral value of the red channel.
 *
 * @return the 16-bit integral (0-65535) value of the red channel
 */
uint16_t tw::Color::getR16 () const {

    return static_cast<uint16_t>(m_r * 65535.f);

}

/**
 * Get the normalized value of the green channel.
 *
 * @return the normalized (0-1) value of the green channel
 */
float tw::Color::getG () const {

    return m_g;

}

/**
 * Get the 8-bit integral value of the green channel.
 *
 * @return the 8-bit integral (0-255) value of the green channel
 */
uint8_t tw::Color::getG8 () const {

    return static_cast<uint8_t>(m_g * 255.f);

}

/**
 * Get the 16-bit integral value of the green channel.
 *
 * @return the 16-bit integral (0-65535) value of the green channel
 */
uint16_t tw::Color::getG16 () const {

    return static_cast<uint16_t>(m_g * 65535.f);

}

/**
 * Get the normalized value of the blue channel.
 *
 * @return the normalized (0-1) value of the blue channel
 */
float tw::Color::getB () const {

    return m_b;

}

/**
 * Get the 8-bit integral value of the blue channel.
 *
 * @return the 8-bit integral (0-255) value of the blue channel
 */
uint8_t tw::Color::getB8 () const {

    return static_cast<uint8_t>(m_b * 255.f);

}

/**
 * Get the 16-bit integral value of the blue channel.
 *
 * @return the 16-bit integral (0-65535) value of the blue channel
 */
uint16_t tw::Color::getB16 () const {

    return static_cast<uint16_t>(m_b * 65535.f);

}
/**
 * Get the normalized value of the alpha channel.
 *
 * @return the normalized (0-1) value of the alpha channel
 */
float tw::Color::getA () const {

    return m_a;

}

/**
 * Get the 8-bit integral value of the alpha channel.
 *
 * @return the 8-bit integral (0-255) value of the alpha channel
 */
uint8_t tw::Color::getA8 () const {

    return static_cast<uint8_t>(m_a * 255.f);

}

/**
 * Get the 16-bit integral value of the alpha channel.
 *
 * @return the 16-bit integral (0-65535) value of the alpha channel
 */
uint16_t tw::Color::getA16 () const {

    return static_cast<uint16_t>(m_a * 65535.f);

}

/**
 * Set the normalized values of the red, green, blue, and alpha channels.
 *
 * @param r the normalized (0-1) value of the red channel
 * @param g the normalized (0-1) value of the green channel
 * @param b the normalized (0-1) value of the blue channel
 * @param a the normalized (0-1) value of the alpha channel
 */
void tw::Color::setRGBA (float r, float g, float b, float a) {

    setR(r);
    setG(g);
    setB(b);
    setA(a);

}

/**
 * Set the 8-bit integral values of the red, green, blue, and alpha channels.
 *
 * @param r the 8-bit integral (0-255) value of the red channel
 * @param g the 8-bit integral (0-255) value of the green channel
 * @param b the 8-bit integral (0-255) value of the blue channel
 * @param a the 8-bit integral (0-255) value of the alpha channel
 */
void tw::Color::setRGBA8 (uint8_t r, uint8_t g, uint8_t b, uint8_t a) {

    setR8(r);
    setG8(g);
    setB8(b);
    setA8(a);

}

/**
 * Set the 16-bit integral values of the red, green, blue, and alpha channels.
 *
 * @param r the 16-bit integral (0-65535) value of the red channel
 * @param g the 16-bit integral (0-65535) value of the green channel
 * @param b the 16-bit integral (0-65535) value of the blue channel
 * @param a the 16-bit integral (0-65535) value of the alpha channel
 */
void tw::Color::setRGBA16 (uint16_t r, uint16_t g, uint16_t b, uint16_t a) {

    setR16(r);
    setG16(g);
    setB16(b);
    setA16(a);

}

/**
 * Set the normalized value of the red channel
 *
 * @param r the normalized (0-1) value of the red channel
 */
void tw::Color::setR (float r) {

    if (r > 1.f) {
        m_r = 1.f;
    } else if (r < 0.f) {
        m_g = 0.f;
    } else {
        m_r = r;
    }

}

/**
 * Set the 8-bit integral value of the red channel.
 *
 * @param r the 8-bit integral (0-255) value of the red channel
 */
void tw::Color::setR8 (uint8_t r) {

    setR(static_cast<float>(r) / 255.f);

}

/**
 * Set the 16-bit integral value of the red channel.
 *
 * @param r the 16-bit integral (0-65535) value of the red channel
 */
void tw::Color::setR16 (uint16_t r) {

    setR(static_cast<float>(r) / 65535.f);

}

/**
 * Set the normalized value of the green channel.
 *
 * @param g the normalized (0-1) value of the green channel
 */
void tw::Color::setG (float g) {

    if (g > 1.f) {
        m_g = 1.f;
    } else if (g < 0.f) {
        m_g = 0.f;
    } else {
        m_g = g;
    }

}

/**
 * Set the 8-bit integral value of the green channel.
 *
 * @param g the 8-bit integral (0-255) value of the green channel
 */
void tw::Color::setG8 (uint8_t g) {

    setG(static_cast<float>(g) / 255.f);

}

/**
 * Set the 16-bit integral value of the green channel.
 *
 * @param g the 16-bit integral (0-65535) value of the green channel
 */
void tw::Color::setG16 (uint16_t g) {

    setG(static_cast<float>(g) / 65535.f);

}

/**
 * Set the normalized value of the blue channel.
 *
 * @param b the normalized (0-1) value of the blue channel
 */
void tw::Color::setB (float b) {

    if (b > 1.f) {
        m_b = 1.f;
    } else if (b < 0.f) {
        m_b = 0.f;
    } else {
        m_b = b;
    }

}

/**
 * Set the 8-bit integral value of the blue channel
 *
 * @param b the 8-bit integral (0-255) value of the blue channel
 */
void tw::Color::setB8 (uint8_t b) {

    setB(static_cast<float>(b) / 255.f);

}

/**
 * Set the 16-bit integral value of the blue channel
 *
 * @param b the 16-bit integral (0-65535) value of the blue channel
 */
void tw::Color::setB16 (uint16_t b) {

    setB(static_cast<float>(b) / 65535.f);

}

/**
 * Set the normalized value of the alpha channel
 *
 * @param a the normalized (0-1) value of the blue channel
 */
void tw::Color::setA (float a) {

    if (a > 1.f) {
        m_a = 1.f;
    } else if (a < 0.f) {
        m_a = 0.f;
    } else {
        m_a = a;
    }

}

/**
 * Set the 8-bit integral value of the alpha channel
 *
 * @param a the 8-bit integral (0-255) value of the alpha channel
 */
void tw::Color::setA8 (uint8_t a) {

    setA(static_cast<float>(a) / 255.f);

}

/**
 * Set the 16-bit integral value of the alpha channel
 *
 * @param a the 16-bit integral (0-65535) value of the alpha channel
 */
void tw::Color::setA16 (uint16_t a) {

    setA(static_cast<float>(a) / 65535.f);

}

/**
 * Lighten the color.
 *
 * @param multiplier value to add
 */
void tw::Color::lighten (float multiplier) {

    float actual = 1.f + multiplier;

    setRGBA(
        getR() * actual,
        getG() * actual,
        getB() * actual,
        getA()
    );

}

/**
 * Get a lightened copy of the color.
 *
 * @param multiplier value to add to copy
 * @return lightened copy of color
 */
tw::Color tw::Color::makeLighten (float multiplier) {

    auto copy = *this;
    copy.lighten(multiplier);
    return copy;

}

/**
 * Darken the color.
 *
 * @param multiplier value to remove
 */
void tw::Color::darken (float multiplier) {

    float actual = 1.f - multiplier;

    setRGBA(
        getR() * actual,
        getG() * actual,
        getB() * actual,
        getA()
    );

}

/**
 * Get a darkened copy of the color.
 *
 * @param multiplier value to remove from copy
 * @return darkened copy of color
 */
tw::Color tw::Color::makeDarken (float multiplier) {

    auto copy = *this;
    copy.darken(multiplier);
    return copy;

}

/**
 * Increase the saturation of the color.
 *
 * @param multiplier saturation to add
 */
void tw::Color::saturate (float multiplier) {

    float avg = ((getR() + getG() + getB()) / 3.f);
    float newR = 0.f;
    float newG = 0.f;
    float newB = 0.f;
    float r = getR();
    float g = getG();
    float b = getB();

    if (r > avg) {
        newR += (r - avg) * multiplier;
    } else if (r < avg) {
        newR -= (avg - r) * multiplier;
    } else {
        newR = r;
    }

    if (g > avg) {
        newG += (g - avg) * multiplier;
    } else if (g < avg) {
        newG -= (avg - g) * multiplier;
    } else {
        newG = g;
    }

    if (b > avg) {
        newB += (b - avg) * multiplier;
    } else if (b < avg) {
        newB -= (avg - b) * multiplier;
    } else {
        newB = b;
    }

    setRGBA(newR, newG, newB, getA());

}

/**
 * Get a saturated copy of the color.
 *
 * @param multiplier saturation to add to copy
 * @return saturated copy of color
 */
tw::Color tw::Color::makeSaturate (float multiplier) {

    auto copy = *this;
    copy.saturate(multiplier);
    return copy;

}

/**
 * Decrease saturation of the color.
 *
 * @param multiplier saturation to remove
 */
void tw::Color::desaturate (float multiplier) {

    saturate(-multiplier);

}

/**
 * Get a desaturated copy of the color.
 *
 * @param multiplier saturation to remove from copy
 * @return desaturated copy of color
 */
tw::Color tw::Color::makeDesaturate (float multiplier) {

    auto copy = *this;
    copy.desaturate(multiplier);
    return copy;

}

/**
 * Check for equality of two tw::Color objects.
 *
 * @param other color with which to compare
 * @return equality of tw::Color objects
 */
bool tw::Color::operator == (const tw::Color& other) const {

    if (
        getR() == other.getR() &&
        getG() == other.getG() &&
        getB() == other.getB() &&
        getA() == other.getA()
    ) {
        return true;
    } else {
        return false;
    }

}

/**
 * Check for inequality of two tw::Color objects.
 *
 * @param other color with which to compare
 * @return inequality of tw::Color objects
 */
bool tw::Color::operator != (const tw::Color& other) const {

    return !(*this == other);

}

/**
 * Add the values of two tw::Color objects.
 *
 * @param other color with which to add
 * @return color with combined values
 */
tw::Color tw::Color::operator + (const tw::Color& other) const {

    auto copy = *this;

    copy.setRGBA(
        copy.getR() + other.getR(),
        copy.getG() + other.getG(),
        copy.getB() + other.getB(),
        copy.getA() + other.getA()
    );

    return copy;

}

/**
 * Add the values of two tw::Color objects (rvalue optimization).
 *
 * @param other color with which to add
 * @return color with combined values
 */
tw::Color tw::Color::operator + (tw::Color&& other) const {

    other.setRGBA(
        getR() + other.getR(),
        getG() + other.getG(),
        getB() + other.getB(),
        getA() + other.getA()
    );

    return other;

}

/**
 * Add the value of a tw::Color and a scalar.
 *
 * @param other scalar with which to add
 * @return color with combined values
 */
tw::Color tw::Color::operator + (float other) const {

    auto copy = *this;

    copy.setRGBA(
        getR() + other,
        getG() + other,
        getB() + other,
        getA() + other
    );

    return copy;

}

/**
 * Increment the value of a tw::Color with another tw::Color.
 *
 * @param other color with which to increment
 * @return self reference after incrementing
 */
tw::Color& tw::Color::operator += (const tw::Color& other) {

    setRGBA(
        getR() + other.getR(),
        getG() + other.getG(),
        getB() + other.getB(),
        getA() + other.getA()
    );

    return *this;

}

/**
 * Increment the value of a tw::Color with a scalar.
 *
 * @param other scalar with which to increment
 * @return self reference after incrementing
 */
tw::Color& tw::Color::operator += (float other) {

    setRGBA(
        getR() + other,
        getG() + other,
        getB() + other,
        getA() + other
    );

    return *this;

}

/**
 * Subtract the value of a tw::Color from a tw::Color.
 *
 * @param other color by which to subtract
 * @return color with subtracted value
 */
tw::Color tw::Color::operator - (const tw::Color& other) const {

    auto copy = *this;

    copy.setRGBA(
        getR() - other.getR(),
        getG() - other.getG(),
        getB() - other.getB(),
        getA() - other.getA()
    );

    return copy;

}

/**
 * Subtract the value of a tw::Color from a tw::Color (rvalue optimization).
 *
 * @param other color by which to subtract
 * @return color with subtracted value
 */
tw::Color tw::Color::operator - (tw::Color&& other) const {

    other.setRGBA(
        getR() - other.getR(),
        getG() - other.getG(),
        getB() - other.getB(),
        getA() - other.getA()
    );

    return other;

}

/**
 * Subtract the value of a scalar from a tw::Color.
 *
 * @param other scalar by which to subtract
 * @return color with subtracted value
 */
tw::Color tw::Color::operator - (float other) const {

    auto copy = *this;

    copy.setRGBA(
        getR() - other,
        getG() - other,
        getB() - other,
        getA() - other
    );

    return copy;

}

/**
 * Decrement the value of a tw::Color from a tw::Color.
 *
 * @param other color by which to decrement
 * @return self reference after decrementing
 */
tw::Color& tw::Color::operator -= (const tw::Color& other) {

    setRGBA(
        getR() - other.getR(),
        getG() - other.getG(),
        getB() - other.getB(),
        getA() - other.getA()
    );

    return *this;

}

/**
 * Decrement the value of a scalar from a tw::Color.
 *
 * @param other scalar by which to decrement
 * @return self reference after decrementing
 */
tw::Color& tw::Color::operator -= (float other) {

    setRGBA(
        getR() - other,
        getG() - other,
        getB() - other,
        getA() - other
    );

    return *this;

}

/**
 * Multiply the value of two tw::Colors.
 *
 * @param other color with which to multiply
 * @return color with multiplied values
 */
tw::Color tw::Color::operator * (const tw::Color& other) const {

    auto copy = *this;

    copy.setRGBA(
        getR() * other.getR(),
        getG() * other.getG(),
        getB() * other.getB(),
        getA() * other.getA()
    );

    return copy;

}

/**
 * Multiply the value of two tw::Colors (rvalue optimization).
 *
 * @param other color with which to multiply
 * @return color with multiplied values
 */
tw::Color tw::Color::operator * (tw::Color&& other) const {

    other.setRGBA(
        getR() * other.getR(),
        getG() * other.getG(),
        getB() * other.getB(),
        getA() * other.getA()
    );

    return other;

}

/**
 * Multiply the value of a tw::Color with a scalar.
 *
 * @param other scalar with which to multiply
 * @return color with multiplied values
 */
tw::Color tw::Color::operator * (float other) const {

    auto copy = *this;

    copy.setRGBA(
        getR() * other,
        getG() * other,
        getB() * other,
        getA() * other
    );

    return copy;

}

/**
 * Multiply-assign the value of a tw::Color with a tw::Color.
 *
 * @param other color with which to multiply
 * @return self reference after multiply-assigning
 */
tw::Color& tw::Color::operator *= (const tw::Color& other) {

    setRGBA(
        getR() * other.getR(),
        getG() * other.getG(),
        getB() * other.getB(),
        getA() * other.getA()
    );

    return *this;

}

/**
 * Multiply-assign the value of a tw::Color with a scalar.
 *
 * @param other scalar with which to multiply
 * @return self reference after multiply-assigning
 */
tw::Color& tw::Color::operator *= (float other) {

    setRGBA(
        getR() * other,
        getG() * other,
        getB() * other,
        getA() * other
    );

    return *this;

}

/**
 * Divide the value of a tw::Color by a tw::Color.
 *
 * @param other color by which to divide
 * @return color with divided values
 */
tw::Color tw::Color::operator / (const tw::Color& other) const {

    auto copy = *this;

    copy.setRGBA(
        getR() / (other.getR()),
        getG() / (other.getG()),
        getB() / (other.getB()),
        getA() / (other.getA())
    );

    return copy;

}

/**
 * Divide the value of a tw::Color by a tw::Color (rvalue optimization)
 *
 * @param other color by which to divide
 * @return color with divided values
 */
tw::Color tw::Color::operator / (tw::Color&& other) const {

    other.setRGBA(
        getR() / (other.getR()),
        getG() / (other.getG()),
        getB() / (other.getB()),
        getA() / (other.getA())
    );

    return other;

}

/**
 * Divide the value of a tw::Color by a scalar
 *
 * @param other scalar by which to divide
 * @return color with divided values
 */
tw::Color tw::Color::operator / (float other) const {

    auto copy = *this;

    copy.setRGBA(
        getR() / other,
        getG() / other,
        getB() / other,
        getA() / other
    );

    return copy;

}

/**
 * Divide-assign the value of a tw::Color by a tw::Color
 *
 * @param other color by which to divide
 * @return self reference after divide-assigning
 */
tw::Color& tw::Color::operator /= (const tw::Color& other) {

    setRGBA(
        getR() / other.getR(),
        getG() / other.getG(),
        getB() / other.getB(),
        getA() / other.getA()
    );

    return *this;

}

/**
 * Divide-assign the value of a tw::Color by a scalar
 *
 * @param other scalar by which to divide
 * @return self reference after divide-assigning
 */
tw::Color& tw::Color::operator /= (float other) {

    setRGBA(
        getR() / other,
        getG() / other,
        getB() / other,
        getA() / other
    );

    return *this;

}
