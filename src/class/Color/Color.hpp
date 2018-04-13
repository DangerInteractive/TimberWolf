#ifndef H_CLASS_COLOR
#define H_CLASS_COLOR

#include <tuple>
#include <cstdint>

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
    std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> getRGBA8 () const;
    std::tuple<uint16_t, uint16_t, uint16_t, uint16_t> getRGBA16 () const;
    float getR () const;
    uint8_t getR8 () const;
    uint16_t getR16 () const;
    float getG () const;
    uint8_t getG8 () const;
    uint16_t getG16 () const;
    float getB () const;
    uint8_t getB8 () const;
    uint16_t getB16 () const;
    float getA () const;
    uint8_t getA8 () const;
    uint16_t getA16 () const;

    void setRGBA (float, float, float, float);
    void setRGBA8 (uint8_t, uint8_t, uint8_t, uint8_t);
    void setRGBA16 (uint16_t, uint16_t, uint16_t, uint16_t);
    void setR (float);
    void setR8 (uint8_t);
    void setR16 (uint16_t);
    void setG (float);
    void setG8 (uint8_t);
    void setG16 (uint16_t);
    void setB (float);
    void setB8 (uint8_t);
    void setB16 (uint16_t);
    void setA (float);
    void setA8 (uint8_t);
    void setA16 (uint16_t);

    void lighten (float);
    Color makeLighten (float);

    void darken (float);
    Color makeDarken (float);

    void saturate (float);
    Color makeSaturate (float);

    void desaturate (float);
    Color makeDesaturate (float);

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
