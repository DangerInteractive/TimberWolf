#include "../../../include/TimberWolf/Core/Pixel.hpp"

tw::Pixel::Pixel (uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept
: m_r(r), m_g(g), m_b(b), m_a(a) {}

tw::Pixel::Pixel (const Color& color) noexcept
:   m_r(color.getR8()),
    m_g(color.getG8()),
    m_b(color.getB8()),
    m_a(color.getA8()) {}

tw::Color tw::Pixel::getColor () const noexcept {

    auto color = Color();
    color.setRGBA8(m_r, m_g, m_b, m_a);

    return color;

}

uint8_t tw::Pixel::getR () const noexcept {

    return m_r;

}

uint8_t tw::Pixel::getG () const noexcept {

    return m_g;

}

uint8_t tw::Pixel::getB () const noexcept {

    return m_b;

}

uint8_t tw::Pixel::getA () const noexcept {

    return m_a;

}

void tw::Pixel::setColor (const Color& color) noexcept {

    m_r = color.getR8();
    m_g = color.getG8();
    m_b = color.getB8();
    m_a = color.getA8();

}

void tw::Pixel::setRGBA (uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept {

    m_r = r;
    m_g = g;
    m_b = b;
    m_a = a;

}
