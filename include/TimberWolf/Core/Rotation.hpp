#ifndef TW_CLASS_ROTATION
#define TW_CLASS_ROTATION

#include "Quaternion.hpp"
#include "Vector3.hpp"

namespace tw {
class Rotation : public Quaternion {

public:

    Rotation () = default;
    Rotation (float, float, float, float) = delete;
    Rotation (float, Vector3) = delete;
    ~Rotation () = default;

    Rotation (Rotation&&) = default;
    Rotation& operator = (Rotation&&) = default;

    Rotation (const Rotation&) = default;
    Rotation& operator = (const Rotation&) = default;

    Rotation (Quaternion&&); // implicit
    Rotation (const Quaternion&); // implicit

    static Rotation fromRadians (float, const Vector3&);
    static Rotation fromDegrees (float, const Vector3&);

    void rotateBy (const tw::Rotation&);
    void rotateByRadians (float, const Vector3&);
    void rotateByDegrees (float, const Vector3&);

    void rotateTo (const tw::Rotation&);
    void rotateToRadians (float, const Vector3&);
    void rotateToDegrees (float, const Vector3&);

    void reset ();

};
}

#endif
