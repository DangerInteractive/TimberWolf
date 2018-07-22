#ifndef TW_CLASS_ROTATION
#define TW_CLASS_ROTATION

#include <glm/gtc/quaternion.hpp>

#include "Vertex.hpp"

namespace tw {
class Rotation {

public:

    Rotation () = default;
    Rotation (float, const Vertex&);
    ~Rotation () = default;

    Rotation (Rotation&&) = default;
    Rotation& operator = (Rotation&&) = default;

    Rotation (const Rotation&) = default;
    Rotation& operator = (const Rotation&) = default;

    const glm::quat& getQuaternion () const;

    Rotation& rotateByRadians (float, const Vertex&);
    Rotation& rotateByDegrees (float, const Vertex&);

    Rotation& rotateToRadians (float, const Vertex&);
    Rotation& rotateToDegrees (float, const Vertex&);

    Rotation& reset ();

private:

    glm::quat m_quaternion {};

};
}

#endif
