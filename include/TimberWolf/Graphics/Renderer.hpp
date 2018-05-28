#ifndef H_TW_RENDERER
#define H_TW_RENDERER

/**
 * @file
 *
 * Header for the tw::Renderer class.
 */

#include "../Core/Color.hpp"
#include "Scene.hpp"
#include "Model.hpp"
#include "Mesh.hpp"

namespace tw {
class Renderer {

public:

    Renderer () = default;
    virtual ~Renderer () = default;

    Renderer (Renderer&&) = default;
    Renderer& operator = (Renderer&&) = default;

    Renderer (const Renderer&) = default;
    Renderer& operator = (const Renderer&) = default;

    virtual void render (const Scene*) = 0;

    virtual void clear (const Color&);
    virtual void clear ();
    virtual void clearColor (const Color&) = 0;
    virtual void clearColor () = 0;
    virtual void clearDepth () = 0;

    virtual void onWindowOpen ();
    virtual void onWindowClose ();

    static Color getDefaultClearColor ();

};
}

#endif
