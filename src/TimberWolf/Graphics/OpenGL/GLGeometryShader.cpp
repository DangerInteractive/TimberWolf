#include "../../../../include/TimberWolf/Graphics/OpenGL/GLGeometryShader.hpp"

/**
 * @class tw::GLGeometryShader
 *
 * Handle for an OpenGL geometry shader (version 3.2+).
 */

/**
 * Default constructor.
 */
tw::GLGeometryShader::GLGeometryShader ()
: GLShader(GL_GEOMETRY_SHADER) {}

/**
 * Constructor taking in the geometry shader source code as a std::string.
 *
 * @param source geometry shader source code
 */
tw::GLGeometryShader::GLGeometryShader (const std::string& source)
: GLShader(GL_GEOMETRY_SHADER, source) {

    compile();

}
