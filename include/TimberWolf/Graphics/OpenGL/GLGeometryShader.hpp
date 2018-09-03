#ifndef TW_CLASS_GLGEOMETRYSHADER
#define TW_CLASS_GLGEOMETRYSHADER

/**
 * @file
 *
 * Header file for the tw::GLGeometryShader class.
 */

#include <string>
#include "GLShader.hpp"

namespace tw {
class GLGeometryShader : public GLShader {

public:

    GLGeometryShader ();
    explicit GLGeometryShader (const std::string&);
    ~GLGeometryShader () = default;

    GLGeometryShader (GLGeometryShader&&) = default;
    GLGeometryShader& operator = (GLGeometryShader&&) = default;

    GLGeometryShader (const GLGeometryShader&) = delete; // not copyable
    GLGeometryShader& operator = (const GLGeometryShader&) = delete;

};
}

#endif
