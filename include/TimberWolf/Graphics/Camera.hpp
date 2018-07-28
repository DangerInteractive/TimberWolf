#ifndef TW_CLASS_CAMERA
#define TW_CLASS_CAMERA

#include "../Core/Transformation.hpp"

namespace tw {
class Camera {

public:

    Camera () = default;
    ~Camera () = default;

    Camera (Camera&&) = default;
    Camera& operator = (Camera&&) = default;

    Camera (const Camera&) = default;
    Camera& operator = (const Camera&) = default;

private:

    Transformation m_tf {};

};
}

#endif
