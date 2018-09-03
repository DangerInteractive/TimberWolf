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
    Color (float, float, float, float);
    ~Color () = default;

    Color (Color&&) = default;
    Color& operator = (Color&&) = default;

    Color (const Color&) = default;
    Color& operator = (const Color&) = default;

    std::tuple<float, float, float, float> getRGBA () const;
    std::tuple<float, float, float, float> getLinearRGBA () const;
    std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> getRGBA8 () const;
    std::tuple<uint16_t, uint16_t, uint16_t, uint16_t> getRGBA16 () const;
    float getR () const;
    float getLinearR () const;
    uint8_t getR8 () const;
    uint16_t getR16 () const;
    float getG () const;
    float getLinearG () const;
    uint8_t getG8 () const;
    uint16_t getG16 () const;
    float getB () const;
    float getLinearB () const;
    uint8_t getB8 () const;
    uint16_t getB16 () const;
    float getA () const;
    uint8_t getA8 () const;
    uint16_t getA16 () const;

    void setRGBA (float, float, float, float);
    void setLinearRGBA (float, float, float, float);
    void setRGBA8 (uint8_t, uint8_t, uint8_t, uint8_t);
    void setRGBA16 (uint16_t, uint16_t, uint16_t, uint16_t);
    void setR (float);
    void setLinearR (float);
    void setR8 (uint8_t);
    void setR16 (uint16_t);
    void setG (float);
    void setLinearG (float);
    void setG8 (uint8_t);
    void setG16 (uint16_t);
    void setB (float);
    void setLinearB (float);
    void setB8 (uint8_t);
    void setB16 (uint16_t);
    void setA (float);
    void setA8 (uint8_t);
    void setA16 (uint16_t);

    void lighten (float);
    Color makeLighten (float) const;

    void darken (float);
    Color makeDarken (float) const;

    void saturate (float);
    Color makeSaturate (float) const;

    void desaturate (float);
    Color makeDesaturate (float) const;

    void interpolate (const Color&, float);
    Color makeInterpolate (const Color&, float) const;

    static Color lighten (const Color&, float);
    static Color darken (const Color&, float);
    static Color saturate (const Color&, float);
    static Color desaturate (const Color&, float);
    static Color interpolate (const Color&, const Color&, float);

    bool operator == (const Color&) const;
    bool operator != (const Color&) const;

    Color operator + (const Color&) const;
    Color operator + (Color&&) const;
    Color operator + (float) const;

    Color& operator += (const Color&);
    Color& operator += (float);

    Color operator - (const Color&) const;
    Color operator - (Color&&) const;
    Color operator - (float) const;

    Color& operator -= (const Color&);
    Color& operator -= (float);

    Color operator * (const Color&) const;
    Color operator * (Color&&) const;
    Color operator * (float) const;

    Color& operator *= (const Color&);
    Color& operator *= (float);

    Color operator / (const Color&) const;
    Color operator / (Color&&) const;
    Color operator / (float) const;

    Color& operator /= (const Color&);
    Color& operator /= (float);

private:

    float m_r {0.f};
    float m_g {0.f};
    float m_b {0.f};
    float m_a {1.f};

};
}

#endif
