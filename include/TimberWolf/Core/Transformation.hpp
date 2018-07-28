#ifndef TW_CLASS_TRANSFORMATION
#define TW_CLASS_TRANSFORMATION

#include <glm/gtc/matrix_transform.hpp>

#include "Matrix4.hpp"
#include "Rotation.hpp"
#include "Vector3.hpp"

namespace tw {
class Transformation : public Matrix4 {

public:

    class Builder {

    public:

        Builder () = default;
        ~Builder () = default;

        Builder (Builder&&) = default;
        Builder& operator = (Builder&&) = default;

        Builder (const Builder&) = default;
        Builder& operator = (const Builder&) = default;

        Builder& setScale (float);
        Builder& setScale (const Vector3&);
        Builder& setScale (float, float, float);
        Builder& setScaleX (float);
        Builder& setScaleY (float);
        Builder& setScaleZ (float);

        Builder& setRotation (const Rotation&);
        Builder& setRotationRadians (float, const Vector3&);
        Builder& setRotationDegrees (float, const Vector3&);

        Builder& setTranslation (const Vector3&);
        Builder& setTranslation (float, float, float);
        Builder& setTranslationX (float);
        Builder& setTranslationY (float);
        Builder& setTranslationZ (float);

        Transformation&& build () &&;
        Transformation build () &;

    private:

        Vector3 m_scale {};
        Rotation m_rotation {};
        Vector3 m_translation {};

    };

    Transformation () = default;
    Transformation (float, const Rotation&, const Vector3&);
    Transformation (const Vector3&, const Rotation&, const Vector3&);
    ~Transformation () = default;

    Transformation (Transformation&&) = default;
    Transformation& operator = (Transformation&&) = default;

    Transformation (const Transformation&) = default;
    Transformation& operator = (const Transformation&) = default;

};
}

#endif
