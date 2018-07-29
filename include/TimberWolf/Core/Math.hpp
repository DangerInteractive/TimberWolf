#ifndef TW_CLASS_MATH
#define TW_CLASS_MATH

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_square_root.hpp>

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

    // fast math, courtest of GLM

    template <typename ...T>
    static auto fastSquareRoot (T... args) {
        return glm::fastSqrt(std::forward<T>(args)...);
    }

    template <typename ...T>
    static auto fastInverseSquareRoot (T... args) {
        return glm::fastInverseSqrt(std::forward<T>(args)...);
    }

    template <typename ...T>
    static auto fastDistance (T... args) {
        return glm::fastDistance(std::forward<T>(args)...);
    }

    template <typename ...T>
    static auto fastLength (T... args) {
        return glm::fastLength(std::forward<T>(args)...);
    }

    template <typename ...T>
    static auto fastNormalize (T... args) {
        return glm::fastNormalize(std::forward<T>(args)...);
    }

};
}

#endif
