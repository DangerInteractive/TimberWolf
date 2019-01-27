#ifndef TW_CLASS_LIGHT
#define TW_CLASS_LIGHT

#include "../Core/Color.hpp"
#include "../Core/Normal.hpp"
#include "../Core/Vertex.hpp"

namespace tw {
class Light {

public:

    Light () = default;
    ~Light () = default;

    Light (Light&&) = default;
    Light& operator = (Light&&) = default;

    Light (const Light&) = default;
    Light& operator = (const Light&) = default;

    Color getColor () const noexcept;
    float getColorR () const noexcept;
    float getColorG () const noexcept;
    float getColorB () const noexcept;
    float getColorA () const noexcept;
    void setColor (Color) noexcept;
    void setColor (float, float, float, float = 1.f) noexcept;
    void setColorR (float) noexcept;
    void setColorG (float) noexcept;
    void setColorB (float) noexcept;
    void setColorA (float) noexcept;

    float getIntensity () const noexcept;
    void setIntensity (float) noexcept;

    bool positionEnabled () const noexcept;
    void enablePosition () noexcept;
    void disablePosition () noexcept;

    Vertex getPosition () const noexcept;
    float getPositionX () const noexcept;
    float getPositionY () const noexcept;
    float getPositionZ () const noexcept;
    void setPosition (Vertex) noexcept;
    void setPosition (float, float, float) noexcept;
    void setPositionX (float) noexcept;
    void setPositionY (float) noexcept;
    void setPositionZ (float) noexcept;

    bool directionEnabled () const noexcept;
    void enableDirection () noexcept;
    void disableDirection () noexcept;

    Normal getDirection () const noexcept;
    float getDirectionX () const noexcept;
    float getDirectionY () const noexcept;
    float getDirectionZ () const noexcept;
    void setDirection (Normal) noexcept;
    void setDirection (float, float, float) noexcept;
    void setDirectionX (float) noexcept;
    void setDirectionY (float) noexcept;
    void setDirectionZ (float) noexcept;

    bool spreadEnabled () const noexcept;
    void enableSpread () noexcept;
    void disableSpread () noexcept;

    float getSpreadRadians () const noexcept;
    float getSpreadDegrees () const noexcept;
    void setSpreadRadians (float) noexcept;
    void setSpreadDegrees (float) noexcept;

private:

    Color m_color {1.f, 1.f, 1.f, 1.f}; // white
    float m_intensity {1.f};

    Vertex m_position {0.f, 0.f, 0.f};
    Normal m_direction {0.f, 0.f, 0.f};
    float m_spreadRadians {0.f};

    bool m_hasPosition {false};
    bool m_hasDirection {false};
    bool m_hasSpread {false};

};
}

#endif
