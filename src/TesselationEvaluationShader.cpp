#include "../include/TesselationEvaluationShader.hpp"

tw::TesselationEvaluationShader::TesselationEvaluationShader ()
: Shader(GL_TESS_EVALUATION_SHADER) {}

tw::TesselationEvaluationShader::TesselationEvaluationShader (const std::string& source)
: Shader(GL_TESS_EVALUATION_SHADER, source) {}
