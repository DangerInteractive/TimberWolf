#include "../include/TesselationEvaluationShader.hpp"

/**
 * @class tw::TesselationEvaluationShader
 *
 * Handle for an OpenGL tesselation evaluation shader (version 4.0+).
 */

tw::TesselationEvaluationShader::TesselationEvaluationShader ()
: Shader(GL_TESS_EVALUATION_SHADER) {}

tw::TesselationEvaluationShader::TesselationEvaluationShader (const std::string& source)
: Shader(GL_TESS_EVALUATION_SHADER, source) {

    compile();

}
