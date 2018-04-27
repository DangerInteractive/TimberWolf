#include "../include/FragmentShader.hpp"

tw::FragmentShader::FragmentShader ()
: Shader(GL_FRAGMENT_SHADER) {}

tw::FragmentShader::FragmentShader (const std::string& source)
: Shader(GL_FRAGMENT_SHADER, source) {}
