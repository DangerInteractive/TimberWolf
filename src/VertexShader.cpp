#include "../include/VertexShader.hpp"

/**
 * @class tw::VertexShader
 *
 * Handle for an OpenGL vertex shader (version 2.0+).
 */

tw::VertexShader::VertexShader ()
: Shader(GL_VERTEX_SHADER) {}

tw::VertexShader::VertexShader (const std::string& source)
: Shader(GL_VERTEX_SHADER, source) {

    compile();

}
