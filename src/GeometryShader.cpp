#include "../include/GeometryShader.hpp"

tw::GeometryShader::GeometryShader ()
: Shader(GL_GEOMETRY_SHADER) {}

tw::GeometryShader::GeometryShader (const std::string& source)
: Shader(GL_GEOMETRY_SHADER, source) {}
