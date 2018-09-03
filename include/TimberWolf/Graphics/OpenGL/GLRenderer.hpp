#ifndef TW_CLASS_GLRENDERER
#define TW_CLASS_GLRENDERER

/**
 * @file
 *
 * Header file for the tw::GLRenderer class.
 */

#include <GL/glew.h>
#include "../Model.hpp"
#include "../../Log/Log.hpp"
#include "../Renderer.hpp"
#include "../../Window/Window.hpp"

namespace tw {
class GLRenderer : public Renderer {

    GLRenderer () = default;
    virtual ~GLRenderer () = default;

    GLRenderer (GLRenderer&&) = default;
    GLRenderer& operator = (GLRenderer&&) = default;

    GLRenderer (const GLRenderer&) = default;
    GLRenderer& operator = (const GLRenderer&) = default;

    virtual void render (const Scene*) override;
    virtual void render (const Model*);

    virtual void clearColor (const Color&) override;
    virtual void clearColor () override;
    virtual void clearDepth () override;

    virtual void onWindowOpen () override;
    virtual void onWindowClose () override;

protected:

    static void glLiveDebug (GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar*, const void*);

    Color m_lastClearColor { getDefaultClearColor() };

};
}

#endif
