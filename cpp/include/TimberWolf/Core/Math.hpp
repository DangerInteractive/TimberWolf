#ifndef TW_CLASS_MATH
#define TW_CLASS_MATH

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/trigonometric.hpp>

namespace tw {
class Math {

public:

    Math () = delete; // static only
    ~Math () = default;

    Math (Math&&) = delete;
    Math& operator = (Math&&) = delete;

    Math (const Math&) = delete;
    Math& operator = (const Math&) = delete;

    // angle unit conversions

    template <typename T>
    static T degreesToRadians (T degrees) {
        return glm::radians(degrees);
    }

    template <typename T>
    static T radiansToDegrees (T radians) {
        return glm::degrees(radians);
    }

};
}

#endif
