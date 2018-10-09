#ifndef TW_CLASS_RENDERER
#define TW_CLASS_RENDERER

/**
 * @file
 *
 * Header for the tw::Renderer class.
 */

#include "../Core/Color.hpp"

#include "Material.hpp"
#include "MaterialHandle.hpp"
#include "Mesh.hpp"
#include "MeshHandle.hpp"
#include "Puppet.hpp"
#include "Scene.hpp"

namespace tw {
class Renderer {

public:

    Renderer () = default;
    virtual ~Renderer () = default;

    Renderer (Renderer&&) = default;
    Renderer& operator = (Renderer&&) = default;

    Renderer (const Renderer&) = default;
    Renderer& operator = (const Renderer&) = default;

    virtual MaterialHandle* put (Material&);
    virtual MeshHandle* put (Mesh&);

    virtual void render (const Scene*);
    virtual void render (const Puppet*) = 0;

    virtual void clear () = 0;
    virtual void clearColor () = 0;
    virtual void clearDepth () = 0;

    virtual void onWindowOpen ();
    virtual void onWindowClose ();

    const Color& getClearColor () const;
    virtual void setClearColor (const Color&);
    void setClearColor (float, float, float, float);
    void resetClearColor ();

protected:

    Color m_clearColor {0.f, 0.f, 0.f, 1.f};

};
}

#endif
