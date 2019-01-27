#ifndef TW_CLASS_GLFRAGMENTSHADER
#define TW_CLASS_GLFRAGMENTSHADER

/**
 * @file
 *
 * Header file for tw::GLFragmentShader class.
 */

#include <string>
#include "GLShader.hpp"

namespace tw {
class GLFragmentShader : public GLShader {

public:

    GLFragmentShader ();
    explicit GLFragmentShader (const std::string&);
    ~GLFragmentShader () = default;

    GLFragmentShader (GLFragmentShader&&) = default;
    GLFragmentShader& operator = (GLFragmentShader&&) = default;

    GLFragmentShader (const GLFragmentShader&) = delete; // not copyable
    GLFragmentShader& operator = (const GLFragmentShader&) = delete;

};
}

#endif
