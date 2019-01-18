#include "../../../../include/TimberWolf/Graphics/OpenGL/GLTesselationControlShader.hpp"

/**
 * @class tw::GLTesselationControlShader
 *
 * Handle for an OpenGL tesselation control shader (version 4.0+).
 */

/**
 * Default constructor.
 */
tw::GLTesselationControlShader::GLTesselationControlShader ()
: GLShader(GL_TESS_CONTROL_SHADER) {}

/**
 * Constructor taking in a std::string of tesselation control shader source
 * code.
 *
 * @param source tesselation control shader source code
 */
tw::GLTesselationControlShader::GLTesselationControlShader (const std::string& source)
: GLShader(GL_TESS_CONTROL_SHADER, source) {

    compile();

}
