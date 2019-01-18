#include "../../../../include/TimberWolf/Graphics/OpenGL/GLTesselationEvaluationShader.hpp"

/**
 * @class tw::GLTesselationEvaluationShader
 *
 * Handle for an OpenGL tesselation evaluation shader (version 4.0+).
 */

/**
 * Default constructor.
 */
tw::GLTesselationEvaluationShader::GLTesselationEvaluationShader ()
: GLShader(GL_TESS_EVALUATION_SHADER) {}

/**
 * Constructor taking in a std::string of tesselation evaluation shader source
 * code.
 *
 * @param source tesselation evaluation shader source code
 */
tw::GLTesselationEvaluationShader::GLTesselationEvaluationShader (const std::string& source)
: GLShader(GL_TESS_EVALUATION_SHADER, source) {

    compile();

}
