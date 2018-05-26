#include "../../../../include/TimberWolf/Graphics/OpenGL/GLFragmentShader.hpp"

/**
 * @class tw::GLFragmentShader
 *
 * Handle for an OpenGL fragment shader (version 2.0+).
 */

/**
 * Default constructor.
 */
tw::GLFragmentShader::GLFragmentShader ()
: GLShader(GL_FRAGMENT_SHADER) {}

/**
 * Constructor taking in the fragment shader source code as a std::string.
 *
 * @param source source code
 */
tw::GLFragmentShader::GLFragmentShader (const std::string& source)
: GLShader(GL_FRAGMENT_SHADER, source) {

    compile();

}
