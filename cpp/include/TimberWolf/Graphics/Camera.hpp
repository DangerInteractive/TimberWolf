#ifndef TW_CLASS_CAMERA
#define TW_CLASS_CAMERA

#include "../Core/Math.hpp"
#include "../Core/Matrix4.hpp"
#include "../Core/Projection.hpp"
#include "../Core/Rotation.hpp"
#include "../Core/Transformation.hpp"
#include "../Core/Vector3.hpp"
#include "../Core/Vertex.hpp"

namespace tw { class Scene; }

namespace tw {
class Camera {

public:

    Camera () = default;
    ~Camera () = default;

    Camera (Camera&&) = default;
    Camera& operator = (Camera&&) = default;

    Camera (const Camera&) = default;
    Camera& operator = (const Camera&) = default;

    Matrix4 getViewProjection ();
    const Matrix4& getViewProjectionRef ();

    Transformation getView ();
    const Transformation& getViewRef ();

    Projection getProjection ();
    const Projection& getProjectionRef ();

    void placeInScene (Scene*);
    void removeFromScene ();

    void setPosition (const Vertex&);
    void setPosition (float, float, float);
    void setPositionX (float);
    void setPositionY (float);
    void setPositionZ (float);

    void setOrientation (const Rotation&);
    void setOrientationRadians (float, const Vector3&);
    void setOrientationDegrees (float, const Vector3&);

    void setFieldOfViewRadians (float);
    void setFieldOfViewDegrees (float);

    void setAspectRatio (float);
    void setDimensions (unsigned int, unsigned int);

    void setFrontPlane (float);
    void setBackPlane (float);

protected:

    void calculateViewMatrix ();
    void calculateProjectionMatrix ();
    void calculateViewProjectionMatrix ();

private:

    Scene* m_scene {nullptr};

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
