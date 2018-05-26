#include "../../../../include/TimberWolf/Graphics/OpenGL/GLVertexShader.hpp"

/**
 * @class tw::GLVertexShader
 *
 * Handle for an OpenGL vertex shader (version 2.0+).
 */

/**
 * Default constructor.
 */
tw::GLVertexShader::GLVertexShader ()
: GLShader(GL_VERTEX_SHADER) {}

/**
 * Constructor taking in a std::string of vertex shader source code.
 *
 * @param source vertex shader source code
 */
tw::GLVertexShader::GLVertexShader (const std::string& source)
: GLShader(GL_VERTEX_SHADER, source) {

    compile();

}
