#include "../../../../include/TimberWolf/Graphics/OpenGL/GLComputeShader.hpp"

/**
 * @class tw::GLComputeShader
 *
 * Handle for an OpenGL compute shader (version 4.3+).
 */

/**
 * Default constructor.
 */
tw::GLComputeShader::GLComputeShader ()
: GLShader(GL_COMPUTE_SHADER) {}

/**
 * Constructor taking in the shader source code as a std::string.
 *
 * @param source compute shader source code
 */
tw::GLComputeShader::GLComputeShader (const std::string& source)
: GLShader(GL_COMPUTE_SHADER, source) {

    compile();

}
