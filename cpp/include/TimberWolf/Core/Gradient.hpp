#ifndef TW_CLASS_GRADIENT
#define TW_CLASS_GRADIENT

#include <map>
#include <cmath>
#include "Color.hpp"

namespace tw {
class Gradient {

public:

    Gradient () = default;
    ~Gradient () = default;

    Gradient (Gradient&&) = default;
    Gradient& operator = (Gradient&&) = default;

    Gradient (const Gradient&) = default;
    Gradient& operator = (const Gradient&) = default;

    Color getColor (float) const;

    Gradient& addPoint (float, const Color&);

private:

    std::map<float, Color> m_points {};
    Color m_colorNaN {};
    Color m_colorPositiveInfinity {};
    Color m_colorNegativeInfinity {};

};
}

#endif
