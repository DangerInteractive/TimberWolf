#include "Color.hpp"

tw::Color::Color (float r, float g, float b, float a) {

    setRGBA(r, g, b, a);

}

std::tuple<float, float, float, float> tw::Color::getRGBA () const {

    return std::make_tuple<float, float, float, float>(
        getR(), getG(), getB(), getA()
    );

}

std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> tw::Color::getRGBA8 () const {

    return std::make_tuple<uint8_t, uint8_t, uint8_t, uint8_t>(
        getR8(), getG8(), getB8(), getA8()
    );

}

std::tuple<uint16_t, uint16_t, uint16_t, uint16_t> tw::Color::getRGBA16 () const {

    return std::make_tuple<uint16_t, uint16_t, uint16_t, uint16_t>(
        getR16(), getG16(), getB16(), getA16()
    );

}

float tw::Color::getR () const {

    return m_r;

}

uint8_t tw::Color::getR8 () const {

    return static_cast<uint8_t>(m_r * 255.f);

}

uint16_t tw::Color::getR16 () const {

    return static_cast<uint16_t>(m_r * 65535.f);

}

float tw::Color::getG () const {

    return m_g;

}

uint8_t tw::Color::getG8 () const {

    return static_cast<uint8_t>(m_g * 255.f);

}

uint16_t tw::Color::getG16 () const {

    return static_cast<uint16_t>(m_g * 65535.f);

}

float tw::Color::getB () const {

    return m_b;

}

uint8_t tw::Color::getB8 () const {

    return static_cast<uint8_t>(m_b * 255.f);

}

uint16_t tw::Color::getB16 () const {

    return static_cast<uint16_t>(m_b * 65535.f);

}

float tw::Color::getA () const {

    return m_a;

}

uint8_t tw::Color::getA8 () const {

    return static_cast<uint8_t>(m_a * 255.f);

}

uint16_t tw::Color::getA16 () const {

    return static_cast<uint16_t>(m_a * 65535.f);

}

void tw::Color::setRGBA (float r, float g, float b, float a) {

    setR(r);
    setG(g);
    setB(b);
    setA(a);

}

void tw::Color::setRGBA8 (uint8_t r, uint8_t g, uint8_t b, uint8_t a) {

    setR8(r);
    setG8(g);
    setB8(b);
    setA8(a);

}

void tw::Color::setRGBA16 (uint16_t r, uint16_t g, uint16_t b, uint16_t a) {

    setR16(r);
    setG16(g);
    setB16(b);
    setA16(a);

}

void tw::Color::setR (float r) {

    if (r > 1.f) {
        m_r = 1.f;
    } else if (r < 0.f) {
        m_g = 0.f;
    } else {
        m_r = r;
    }

}

void tw::Color::setR8 (uint8_t r) {

    setR(static_cast<float>(r) / 255.f);

}

void tw::Color::setR16 (uint16_t r) {

    setR(static_cast<float>(r) / 65535.f);

}

void tw::Color::setG (float g) {

    if (g > 1.f) {
        m_g = 1.f;
    } else if (g < 0.f) {
        m_g = 0.f;
    } else {
        m_g = g;
    }

}

void tw::Color::setG8 (uint8_t g) {

    setG(static_cast<float>(g) / 255.f);

}

void tw::Color::setG16 (uint16_t g) {

    setG(static_cast<float>(g) / 65535.f);

}

void tw::Color::setB (float b) {

    if (b > 1.f) {
        m_b = 1.f;
    } else if (b < 0.f) {
        m_b = 0.f;
    } else {
        m_b = b;
    }

}

void tw::Color::setB8 (uint8_t b) {

    setB(static_cast<float>(b) / 255.f);

}

void tw::Color::setB16 (uint16_t b) {

    setB(static_cast<float>(b) / 65535.f);

}

void tw::Color::setA (float a) {

    if (a > 1.f) {
        m_a = 1.f;
    } else if (a < 0.f) {
        m_a = 0.f;
    } else {
        m_a = a;
    }

}

void tw::Color::setA8 (uint8_t a) {

    setA(static_cast<float>(a) / 255.f);

}

void tw::Color::setA16 (uint16_t a) {

    setA(static_cast<float>(a) / 65535.f);

}

void tw::Color::lighten (float multiplier) {

    float actual = 1.f + multiplier;

    setRGBA(
        getR() * actual,
        getG() * actual,
        getB() * actual,
        getA() * actual
    );

}

tw::Color tw::Color::makeLighten (float multiplier) {

    auto copy = *this;
    copy.lighten(multiplier);
    return copy;

}

void tw::Color::darken (float multiplier) {

    float actual = 1.f - multiplier;

    setRGBA(
        getR() * actual,
        getG() * actual,
        getB() * actual,
        getA() * actual
    );

}

tw::Color tw::Color::makeDarken (float multiplier) {

    auto copy = *this;
    copy.darken(multiplier);
    return copy;

}

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

tw::Color tw::Color::makeSaturate (float multiplier) {

    auto copy = *this;
    copy.saturate(multiplier);
    return copy;

}

void tw::Color::desaturate (float multiplier) {

    saturate(-multiplier);

}

tw::Color tw::Color::makeDesaturate (float multiplier) {

    auto copy = *this;
    copy.desaturate(multiplier);
    return copy;

}

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

bool tw::Color::operator != (const tw::Color& other) const {

    return !(*this == other);

}

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

tw::Color tw::Color::operator + (tw::Color&& other) const {

    other.setRGBA(
        getR() + other.getR(),
        getG() + other.getG(),
        getB() + other.getB(),
        getA() + other.getA()
    );

    return other;

}

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

tw::Color& tw::Color::operator += (const tw::Color& other) {

    setRGBA(
        getR() + other.getR(),
        getG() + other.getG(),
        getB() + other.getB(),
        getA() + other.getA()
    );

    return *this;

}

tw::Color& tw::Color::operator += (float other) {

    setRGBA(
        getR() + other,
        getG() + other,
        getB() + other,
        getA() + other
    );

    return *this;

}

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

tw::Color tw::Color::operator - (tw::Color&& other) const {

    other.setRGBA(
        getR() - other.getR(),
        getG() - other.getG(),
        getB() - other.getB(),
        getA() - other.getA()
    );

    return other;

}

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

tw::Color& tw::Color::operator -= (const tw::Color& other) {

    setRGBA(
        getR() - other.getR(),
        getG() - other.getG(),
        getB() - other.getB(),
        getA() - other.getA()
    );

    return *this;

}

tw::Color& tw::Color::operator -= (float other) {

    setRGBA(
        getR() - other,
        getG() - other,
        getB() - other,
        getA() - other
    );

    return *this;

}

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

tw::Color tw::Color::operator * (tw::Color&& other) const {

    other.setRGBA(
        getR() * other.getR(),
        getG() * other.getG(),
        getB() * other.getB(),
        getA() * other.getA()
    );

    return other;

}

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

tw::Color& tw::Color::operator *= (const tw::Color& other) {

    setRGBA(
        getR() * other.getR(),
        getG() * other.getG(),
        getB() * other.getB(),
        getA() * other.getA()
    );

    return *this;

}

tw::Color& tw::Color::operator *= (float other) {

    setRGBA(
        getR() * other,
        getG() * other,
        getB() * other,
        getA() * other
    );

    return *this;

}

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

tw::Color tw::Color::operator / (tw::Color&& other) const {

    other.setRGBA(
        getR() / (other.getR()),
        getG() / (other.getG()),
        getB() / (other.getB()),
        getA() / (other.getA())
    );

    return other;

}

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

tw::Color& tw::Color::operator /= (const tw::Color& other) {

    setRGBA(
        getR() / other.getR(),
        getG() / other.getG(),
        getB() / other.getB(),
        getA() / other.getA()
    );

    return *this;

}

tw::Color& tw::Color::operator /= (float other) {

    setRGBA(
        getR() / other,
        getG() / other,
        getB() / other,
        getA() / other
    );

    return *this;

}
