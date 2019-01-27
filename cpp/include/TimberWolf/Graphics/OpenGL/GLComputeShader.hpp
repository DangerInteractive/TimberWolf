#ifndef TW_CLASS_GLCOMPUTESHADER
#define TW_CLASS_GLCOMPUTESHADER

/**
 * @file
 *
 * Header file for the tw::GLComputeShader class.
 */

#include <string>
#include "GLShader.hpp"

namespace tw {
class GLComputeShader : public GLShader {

public:

    GLComputeShader ();
    explicit GLComputeShader (const std::string&);
    ~GLComputeShader () = default;

    GLComputeShader (GLComputeShader&&) = default;
    GLComputeShader& operator = (GLComputeShader&&) = default;

    GLComputeShader (const GLComputeShader&) = delete; // not copyable
    GLComputeShader& operator = (const GLComputeShader&) = delete;

};
}

#endif
