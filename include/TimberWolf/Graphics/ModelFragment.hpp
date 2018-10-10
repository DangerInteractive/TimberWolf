#ifndef TW_CLASS_MODELFRAGMENT
#define TW_CLASS_MODELFRAGMENT

#include <memory>

#include "../Core/Transformation.hpp"

#include "Material.hpp"
#include "MaterialHandle.hpp"
#include "Mesh.hpp"
#include "MeshHandle.hpp"

namespace tw {
class ModelFragment {

public:

    ModelFragment () = default;
    ~ModelFragment () = default;

    ModelFragment (ModelFragment&&) = default;
    ModelFragment& operator = (ModelFragment&&) = default;

    ModelFragment (const ModelFragment&) = default;
    ModelFragment& operator = (const ModelFragment&) = default;

    Mesh* getMesh () const;
    void setMesh (const std::shared_ptr<Mesh>&);

    Material* getMaterial () const;
    void setMaterial (const std::shared_ptr<Material>&);

    const Transformation& getTransformation () const;
    void setTransformation (Transformation&&);
    void setTransformation (const Transformation&);

private:

    std::shared_ptr<Mesh> m_mesh {nullptr};
    std::shared_ptr<Material> m_material {nullptr};

    Transformation m_transformation {};

};
}

#endif
