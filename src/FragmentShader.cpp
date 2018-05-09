#include "../include/FragmentShader.hpp"

/**
 * @class tw::FragmentShader
 *
 * Handle for an OpenGL fragment shader (version 2.0+).
 */

tw::FragmentShader::FragmentShader ()
: Shader(GL_FRAGMENT_SHADER) {}

tw::FragmentShader::FragmentShader (const std::string& source)
: Shader(GL_FRAGMENT_SHADER, source) {

    compile();

}
