#ifndef TW_CLASS_PROJECTION
#define TW_CLASS_PROJECTION

#include <glm/gtc/matrix_transform.hpp>

#include "Matrix4.hpp"

namespace tw {
class Projection : public Matrix4 {

public:

    class Builder {

    public:

        Builder () = default;
        ~Builder () = default;

        Builder (Builder&&) = default;
        Builder& operator = (Builder&&) = default;

        Builder (const Builder&) = default;
        Builder& operator = (const Builder&) = default;

        Builder& setFieldOfViewRadians (float);
        Builder& setFieldOfViewDegrees (float);

        Builder& setAspectRatio (float);

        Builder& setNearPlane (float);
        Builder& setFarPlane (float);

        Projection&& build () &&;
        Projection build () &;

    private:

        float m_fovDegrees {90.f};
        float m_aspectRatio {1.f};
        float m_nearPlane {0.f};
        float m_farPlane {4096.f};

    };

    Projection () = default;
    Projection (Matrix4&&); // implicit
    Projection (const Matrix4&); // implicit
    Projection (float, float, float, float);
    ~Projection () = default;

    Projection (Projection&&) = default;
    Projection& operator = (Projection&&) = default;

    Projection (const Projection&) = default;
    Projection& operator = (const Projection&) = default;

};
}

#endif
