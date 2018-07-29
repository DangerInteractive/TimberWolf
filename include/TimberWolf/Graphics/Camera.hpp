#ifndef TW_CLASS_CAMERA
#define TW_CLASS_CAMERA

#include "../Core/Math.hpp"
#include "../Core/Matrix4.hpp"
#include "../Core/Projection.hpp"
#include "../Core/Rotation.hpp"
#include "../Core/Transformation.hpp"
#include "../Core/Vector3.hpp"
#include "../Core/Vertex.hpp"

namespace tw {
class Camera {

public:

    Camera () = default;
    ~Camera () = default;

    Camera (Camera&&) = default;
    Camera& operator = (Camera&&) = default;

    Camera (const Camera&) = default;
    Camera& operator = (const Camera&) = default;

    Matrix4 getViewProjection () const;
    const Matrix4& getViewProjectionRef () const;

    Transformation getView () const;
    const Transformation& getViewRef () const;

    Projection getProjection () const;
    const Projection& getProjectionRef () const;

    // transactional changes

    Camera& setPosition (const Vertex&);
    Camera& setPosition (float, float, float);
    Camera& setPositionX (float);
    Camera& setPositionY (float);
    Camera& setPositionZ (float);

    Camera& setOrientation (const Rotation&);
    Camera& setOrientationRadians (float, const Vector3&);
    Camera& setOrientationDegrees (float, const Vector3&);

    Camera& setFieldOfViewRadians (float);
    Camera& setFieldOfViewDegrees (float);

    Camera& setAspectRatio (float);
    Camera& setDimensions (unsigned int, unsigned int);

    Camera& setFrontPlane (float);
    Camera& setBackPlane (float);

    void commit ();

private:

    Vertex m_position {};
    Rotation m_orientation {};
    bool m_dirtyView {false};

    float m_fovDegrees {90.f};
    float m_aspectRatio {1.f};
    float m_frontPlane {0.f};
    float m_backPlane {4096.f};
    bool m_dirtyProjection {false};

    Transformation m_view {1.f, m_orientation, m_position};
    Projection m_projection {m_fovDegrees, m_aspectRatio, m_frontPlane, m_backPlane};

    Matrix4 m_viewProjection {m_view * m_projection};

};
}

#endif
