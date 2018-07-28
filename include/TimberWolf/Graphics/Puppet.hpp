#ifndef TW_CLASS_PUPPET
#define TW_CLASS_PUPPET

#include <memory>

#include "../Core/Rotation.hpp"
#include "../Core/Vertex.hpp"

#include "Material.hpp"
#include "Model.hpp"

namespace tw {
class Puppet {

public:

    Puppet () = default;
    ~Puppet () = default;

    Puppet (Puppet&&) = default;
    Puppet& operator = (Puppet&&) = default;

    Puppet (const Puppet&) = default;
    Puppet& operator = (const Puppet&) = default;

private:

    std::shared_ptr<Model> m_model;
    std::shared_ptr<Material> m_material;

};
}

#endif
