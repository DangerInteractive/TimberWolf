#include "../include/TesselationControlShader.hpp"

/**
 * @class tw::TesselationControlShader
 *
 * Handle for an OpenGL tesselation control shader (version 4.0+).
 */

tw::TesselationControlShader::TesselationControlShader ()
: Shader(GL_TESS_CONTROL_SHADER) {}

tw::TesselationControlShader::TesselationControlShader (const std::string& source)
: Shader(GL_TESS_CONTROL_SHADER, source) {

    compile();

}
