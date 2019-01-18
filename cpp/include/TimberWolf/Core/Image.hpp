#ifndef TW_CLASS_IMAGE
#define TW_CLASS_IMAGE

#include <vector>

#include "Pixel.hpp"

namespace tw {
class Image {

public:

    Image () = default;
    ~Image () = default;

    Image (Image&&) = default;
    Image& operator = (Image&&) = default;

    Image (const Image&) = default;
    Image& operator = (const Image&) = default;

    unsigned int getWidth () const noexcept;
    unsigned int getHeight () const noexcept;

    Pixel getPixel (unsigned int) const;
    Pixel getPixel (unsigned int, unsigned int) const;

    void setWidth (unsigned int);
    void setHeight (unsigned int);

    void setPixel (unsigned int, Pixel);
    void setPixel (unsigned int, unsigned int, Pixel);

private:

    unsigned int m_width {0};
    unsigned int m_height {0};

    std::vector<Pixel> m_pixels {};

};
}

#endif
