#ifndef TW_CLASS_PIXEL
#define TW_CLASS_PIXEL

#include <algorithm>
#include <cstdint>

#include "Color.hpp"

namespace tw {
class Pixel {

public:

    Pixel () = default;
    Pixel (uint8_t, uint8_t, uint8_t, uint8_t) noexcept;
    explicit Pixel (const Color&) noexcept;
    ~Pixel () = default;

    Color getColor () const noexcept;
    uint8_t getR () const noexcept;
    uint8_t getG () const noexcept;
    uint8_t getB () const noexcept;
    uint8_t getA () const noexcept;

    void setColor (const Color&) noexcept;
    void setRGBA (uint8_t, uint8_t, uint8_t, uint8_t) noexcept;
    void setR (uint8_t) noexcept;
    void setG (uint8_t) noexcept;
    void setB (uint8_t) noexcept;
    void setA (uint8_t) noexcept;

    uint8_t m_r {0};
    uint8_t m_g {0};
    uint8_t m_b {0};
    uint8_t m_a {0};

};
}

#endif
