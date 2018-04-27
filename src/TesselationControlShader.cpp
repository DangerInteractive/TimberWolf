#include "../include/TesselationControlShader.hpp"

tw::TesselationControlShader::TesselationControlShader ()
: Shader(GL_TESS_CONTROL_SHADER) {}

tw::TesselationControlShader::TesselationControlShader (const std::string& source)
: Shader(GL_TESS_CONTROL_SHADER, source) {}
