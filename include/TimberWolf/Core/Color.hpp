#ifndef TW_CLASS_COLOR
#define TW_CLASS_COLOR

/**
 * @file
 *
 * Header file for the tw::Color class.
 */

#include <tuple>
#include <cstdint>
#include <cmath>
#include <algorithm>

namespace tw {
class Color {

public:

    Color () = default;
    Color (float, float, float, float) noexcept;
    ~Color () = default;

    Color (Color&&) = default;
    Color& operator = (Color&&) = default;

    Color (const Color&) = default;
    Color& operator = (const Color&) = default;

    std::tuple<float, float, float, float> getRGBA () const noexcept;
    std::tuple<float, float, float, float> getLinearRGBA () const noexcept;
    std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> getRGBA8 () const noexcept;
    std::tuple<uint16_t, uint16_t, uint16_t, uint16_t> getRGBA16 () const noexcept;
    float getR () const noexcept;
    float getLinearR () const noexcept;
    uint8_t getR8 () const noexcept;
    uint16_t getR16 () const noexcept;
    float getG () const noexcept;
    float getLinearG () const noexcept;
    uint8_t getG8 () const noexcept;
    uint16_t getG16 () const noexcept;
    float getB () const noexcept;
    float getLinearB () const noexcept;
    uint8_t getB8 () const noexcept;
    uint16_t getB16 () const noexcept;
    float getA () const noexcept;
    uint8_t getA8 () const noexcept;
    uint16_t getA16 () const noexcept;

    void setRGBA (float, float, float, float) noexcept;
    void setLinearRGBA (float, float, float, float) noexcept;
    void setRGBA8 (uint8_t, uint8_t, uint8_t, uint8_t) noexcept;
    void setRGBA16 (uint16_t, uint16_t, uint16_t, uint16_t) noexcept;
    void setR (float) noexcept;
    void setLinearR (float) noexcept;
    void setR8 (uint8_t) noexcept;
    void setR16 (uint16_t) noexcept;
    void setG (float) noexcept;
    void setLinearG (float) noexcept;
    void setG8 (uint8_t) noexcept;
    void setG16 (uint16_t) noexcept;
    void setB (float) noexcept;
    void setLinearB (float) noexcept;
    void setB8 (uint8_t) noexcept;
    void setB16 (uint16_t) noexcept;
    void setA (float) noexcept;
    void setA8 (uint8_t) noexcept;
    void setA16 (uint16_t) noexcept;

    void lighten (float) noexcept;
    Color makeLighten (float) const noexcept;

    void darken (float) noexcept;
    Color makeDarken (float) const noexcept;

    void saturate (float) noexcept;
    Color makeSaturate (float) const noexcept;

    void desaturate (float) noexcept;
    Color makeDesaturate (float) const noexcept;

    void interpolate (const Color&, float) noexcept;
    Color makeInterpolate (const Color&, float) const noexcept;

    static Color lighten (const Color&, float) noexcept;
    static Color darken (const Color&, float) noexcept;
    static Color saturate (const Color&, float) noexcept;
    static Color desaturate (const Color&, float) noexcept;
    static Color interpolate (const Color&, const Color&, float) noexcept;

    bool operator == (const Color&) const noexcept;
    bool operator != (const Color&) const noexcept;

    Color operator + (const Color&) const noexcept;
    Color operator + (Color&&) const noexcept;
    Color operator + (float) const noexcept;

    Color& operator += (const Color&) noexcept;
    Color& operator += (float) noexcept;

    Color operator - (const Color&) const noexcept;
    Color operator - (Color&&) const noexcept;
    Color operator - (float) const noexcept;

    Color& operator -= (const Color&) noexcept;
    Color& operator -= (float) noexcept;

    Color operator * (const Color&) const noexcept;
    Color operator * (Color&&) const noexcept;
    Color operator * (float) const noexcept;

    Color& operator *= (const Color&) noexcept;
    Color& operator *= (float) noexcept;

    Color operator / (const Color&) const noexcept;
    Color operator / (Color&&) const noexcept;
    Color operator / (float) const noexcept;

    Color& operator /= (const Color&) noexcept;
    Color& operator /= (float) noexcept;

private:

    float m_r {0.f};
    float m_g {0.f};
    float m_b {0.f};
    float m_a {1.f};

};
}

#endif
