#ifndef TW_CLASS_ROTATION
#define TW_CLASS_ROTATION

#include "Quaternion.hpp"
#include "Vector3.hpp"

namespace tw {
class Rotation {

public:

    Rotation () = default;
    Rotation (Quaternion); // implicit
    Rotation (float, const Vector3&);
    ~Rotation () = default;

    Rotation (Rotation&&) = default;
    Rotation& operator = (Rotation&&) = default;

    Rotation (const Rotation&) = default;
    Rotation& operator = (const Rotation&) = default;

    Quaternion getQuaternion () const;
    const Quaternion& getQuaternionRef () const;

    Rotation& rotateBy (const tw::Rotation&);
    Rotation& rotateByRadians (float, const Vector3&);
    Rotation& rotateByDegrees (float, const Vector3&);

    Rotation& rotateTo (const tw::Rotation&);
    Rotation& rotateToRadians (float, const Vector3&);
    Rotation& rotateToDegrees (float, const Vector3&);

    Rotation& reset ();

    operator Quaternion () const; // implicit

    Rotation operator * (float) const;
    Rotation& operator *= (float);

private:

    Quaternion m_quaternion {};

};
}

#endif
