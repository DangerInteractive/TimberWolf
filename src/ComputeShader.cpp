#include "../include/ComputeShader.hpp"

/**
 * @class tw::ComputeShader
 *
 * Handle for an OpenGL compute shader (version 4.3+).
 */

tw::ComputeShader::ComputeShader ()
: Shader(GL_COMPUTE_SHADER) {}

tw::ComputeShader::ComputeShader (const std::string& source)
: Shader(GL_COMPUTE_SHADER, source) {

    compile();

}
