#include "../include/VertexShader.hpp"

/**
 * @class tw::VertexShader
 *
 * Handle for an OpenGL vertex shader (version 2.0+).
 */

/**
 * Default constructor.
 */
tw::VertexShader::VertexShader ()
: Shader(GL_VERTEX_SHADER) {}

/**
 * Constructor taking in a std::string of vertex shader source code.
 *
 * @param source vertex shader source code
 */
tw::VertexShader::VertexShader (const std::string& source)
: Shader(GL_VERTEX_SHADER, source) {

    compile();

}
