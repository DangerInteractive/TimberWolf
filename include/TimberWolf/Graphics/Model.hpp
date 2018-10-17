#ifndef TW_CLASS_MODEL
#define TW_CLASS_MODEL

/**
 * @file
 *
 * Header file for the tw::Model class.
 */

#include <memory>

#include "../Core/Normal.hpp"
#include "../Core/Rotation.hpp"
#include "../Core/Transformation.hpp"
#include "../Core/Vector3.hpp"
#include "../Core/Vertex.hpp"

#include "Material.hpp"
#include "Mesh.hpp"

namespace tw {
class Model {

public:

    Model () = default;
    ~Model () = default;

    Model (Model&&) = default;
    Model& operator = (Model&&) = default;

    Model (const Model&) = default;
    Model& operator = (const Model&) = default;

    Mesh* getMesh () noexcept;
    const Mesh* getMesh () const noexcept;
    std::shared_ptr<Mesh> getMeshShared () noexcept;
    const std::shared_ptr<Mesh> getMeshShared () const noexcept;
    void setMesh (const std::shared_ptr<Mesh>&);
    void setMesh (Mesh*);

    Material* getMaterial () noexcept;
    const Material* getMaterial () const noexcept;
    std::shared_ptr<Material> getMaterialShared () noexcept;
    const std::shared_ptr<Material> getMaterialShared () const noexcept;
    void setMaterial (const std::shared_ptr<Material>&);
    void setMaterial (Material*);

    const Vector3& getScale () const noexcept;
    const Rotation& getRotation () const noexcept;
    const Vertex& getTranslation () const noexcept;
    const Transformation& getTransform () noexcept;
    void setTransform (const Vector3&, const Rotation&, const Vertex&);
    void setTranslation (const Vertex&);
    void setTranslation (float, float, float);
    void setRotation (const Rotation&);
    void setRotationRadians (float, const Normal&);
    void setRotationDegrees (float, const Normal&);
    void setScale (float);
    void setScale (const Vector3&);
    void setScale (float, float, float);

private:

    void calculateTransform () noexcept;

    std::shared_ptr<Mesh> m_mesh {nullptr};
    std::shared_ptr<Material> m_material {nullptr};

    Vector3 m_scale {0.f, 0.f, 0.f};
    Rotation m_rotation {};
    Vertex m_translation {0.f, 0.f, 0.f};

    bool m_dirtyTransform {true};
    Transformation m_transform {};

};
}

#endif
