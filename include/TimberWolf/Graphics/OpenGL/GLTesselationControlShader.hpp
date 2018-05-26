#ifndef H_TW_GLTESSELATIONCONTROLSHADER
#define H_TW_GLTESSELATIONCONTROLSHADER

/**
 * @file
 *
 * Header file for the tw::GLTesselationControlShader class.
 */

#include <string>
#include "GLShader.hpp"

namespace tw {
class GLTesselationControlShader : public GLShader {

public:

    GLTesselationControlShader ();
    explicit GLTesselationControlShader (const std::string&);
    ~GLTesselationControlShader () = default;

    GLTesselationControlShader (GLTesselationControlShader&&) = default;
    GLTesselationControlShader& operator = (GLTesselationControlShader&&) = default;

    GLTesselationControlShader (const GLTesselationControlShader&) = default;
    GLTesselationControlShader& operator = (const GLTesselationControlShader&) = default;

};
}

#endif
