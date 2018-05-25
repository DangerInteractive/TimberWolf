#include "../../../../include/TimberWolf/Graphics/OpenGL/FragmentShader.hpp"

/**
 * @class tw::FragmentShader
 *
 * Handle for an OpenGL fragment shader (version 2.0+).
 */

/**
 * Default constructor.
 */
tw::FragmentShader::FragmentShader ()
: Shader(GL_FRAGMENT_SHADER) {}

/**
 * Constructor taking in the fragment shader source code as a std::string.
 *
 * @param source source code
 */
tw::FragmentShader::FragmentShader (const std::string& source)
: Shader(GL_FRAGMENT_SHADER, source) {

    compile();

}
