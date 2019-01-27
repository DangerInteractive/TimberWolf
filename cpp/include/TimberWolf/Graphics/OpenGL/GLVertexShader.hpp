#ifndef TW_CLASS_GLVERTEXSHADER
#define TW_CLASS_GLVERTEXSHADER

/**
 * @file
 *
 * Header file for the tw::GLVertexShader class.
 */

#include <string>
#include "GLShader.hpp"

namespace tw {
class GLVertexShader : public GLShader {

public:

    GLVertexShader ();
    explicit GLVertexShader (const std::string&);
    ~GLVertexShader () = default;

    GLVertexShader (GLVertexShader&&) = default;
    GLVertexShader& operator = (GLVertexShader&&) = default;

    GLVertexShader (const GLVertexShader&) = delete; // not copyable
    GLVertexShader& operator = (const GLVertexShader&) = delete;

};
}

#endif
