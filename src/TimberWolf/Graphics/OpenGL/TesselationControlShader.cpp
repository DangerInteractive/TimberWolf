#include "../../../../include/TimberWolf/Graphics/OpenGL/TesselationControlShader.hpp"

/**
 * @class tw::TesselationControlShader
 *
 * Handle for an OpenGL tesselation control shader (version 4.0+).
 */

/**
 * Default constructor.
 */
tw::TesselationControlShader::TesselationControlShader ()
: Shader(GL_TESS_CONTROL_SHADER) {}

/**
 * Constructor taking in a std::string of tesselation control shader source
 * code.
 *
 * @param source tesselation control shader source code
 */
tw::TesselationControlShader::TesselationControlShader (const std::string& source)
: Shader(GL_TESS_CONTROL_SHADER, source) {

    compile();

}
