#include "../../../../include/TimberWolf/Graphics/OpenGL/ComputeShader.hpp"

/**
 * @class tw::ComputeShader
 *
 * Handle for an OpenGL compute shader (version 4.3+).
 */

/**
 * Default constructor.
 */
tw::ComputeShader::ComputeShader ()
: Shader(GL_COMPUTE_SHADER) {}

/**
 * Constructor taking in the shader source code as a std::string.
 *
 * @param source compute shader source code
 */
tw::ComputeShader::ComputeShader (const std::string& source)
: Shader(GL_COMPUTE_SHADER, source) {

    compile();

}
