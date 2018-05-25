#include "../../../../include/TimberWolf/Graphics/OpenGL/TesselationEvaluationShader.hpp"

/**
 * @class tw::TesselationEvaluationShader
 *
 * Handle for an OpenGL tesselation evaluation shader (version 4.0+).
 */

/**
 * Default constructor.
 */
tw::TesselationEvaluationShader::TesselationEvaluationShader ()
: Shader(GL_TESS_EVALUATION_SHADER) {}

/**
 * Constructor taking in a std::string of tesselation evaluation shader source
 * code.
 *
 * @param source tesselation evaluation shader source code
 */
tw::TesselationEvaluationShader::TesselationEvaluationShader (const std::string& source)
: Shader(GL_TESS_EVALUATION_SHADER, source) {

    compile();

}
