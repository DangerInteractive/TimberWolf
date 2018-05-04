#include "../include/ComputeShader.hpp"

tw::ComputeShader::ComputeShader ()
: Shader(GL_COMPUTE_SHADER) {}

tw::ComputeShader::ComputeShader (const std::string& source)
: Shader(GL_COMPUTE_SHADER, source) {

    compile();

}
