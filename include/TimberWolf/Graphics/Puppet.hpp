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

    const Vertex& getPosition () const;
    float getPositionX () const;
    float getPositionY () const;
    float getPositionZ () const;
    const Vertex& getHandle () const;
    float getHandleX () const;
    float getHandleY () const;
    float getHandleZ () const;
    const Rotation& getOrientation () const;

    Puppet& translateBy (const Vertex&);
    Puppet& translateBy (float, float, float);
    Puppet& translateXBy (float);
    Puppet& translateYBy (float);
    Puppet& translateZBy (float);

    Puppet& translateTo (const Vertex&);
    Puppet& translateTo (float, float, float);
    Puppet& translateXTo (float);
    Puppet& translateYTo (float);
    Puppet& translateZTo (float);

    Puppet& moveHandleBy (const Vertex&);
    Puppet& moveHandleBy (float, float, float);
    Puppet& moveHandleXBy (float);
    Puppet& moveHandleYBy (float);
    Puppet& moveHandleZBy (float);

    Puppet& moveHandleTo (const Vertex&);
    Puppet& moveHandleTo (float, float, float);
    Puppet& moveHandleXTo (float);
    Puppet& moveHandleYTo (float);
    Puppet& moveHandleZTo (float);

    Puppet& rotateByRadians (float, const Vertex&);
    Puppet& rotateByDegrees (float, const Vertex&);

    Puppet& rotateToRadians (float, const Vertex&);
    Puppet& rotateToDegrees (float, const Vertex&);

private:

    std::shared_ptr<Model> m_model;
    std::shared_ptr<Material> m_material;

    Vertex m_position {0.f, 0.f, 0.f};
    Vertex m_handle {0.f, 0.f, 0.f};
    Rotation m_orientation {};

};
}

#endif
