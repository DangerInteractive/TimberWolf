#include "../../../include/TimberWolf/Core/Image.hpp"

unsigned int tw::Image::getWidth () const noexcept {

    return m_width;

}

unsigned int tw::Image::getHeight () const noexcept {

    return m_height;

}

tw::Pixel tw::Image::getPixel (unsigned int index) const {

    return m_pixels.at(index);

}

tw::Pixel tw::Image::getPixel (unsigned int x, unsigned int y) const {

    return getPixel((y * m_width) + x);

}

void tw::Image::setWidth (unsigned int width) {

    m_width = width;
    m_pixels.reserve(width * m_height);

}

void tw::Image::setHeight (unsigned int height) {

    m_height = height;
    m_pixels.reserve(height * m_width);

}

void tw::Image::setPixel (unsigned int index, Pixel pixel) {

    m_pixels.at(index) = pixel;

}

void tw::Image::setPixel (unsigned int x, unsigned int y, Pixel pixel) {

    setPixel((y * m_width) + x, pixel);

}
