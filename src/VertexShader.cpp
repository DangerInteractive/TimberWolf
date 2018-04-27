#include "../include/VertexShader.hpp"

tw::VertexShader::VertexShader ()
: Shader(GL_VERTEX_SHADER) {}

tw::VertexShader::VertexShader (const std::string& source)
: Shader(GL_VERTEX_SHADER, source) {}
