#include "../../../../include/TimberWolf/Graphics/OpenGL/GeometryShader.hpp"

/**
 * @class tw::GeometryShader
 *
 * Handle for an OpenGL geometry shader (version 3.2+).
 */

/**
 * Default constructor.
 */
tw::GeometryShader::GeometryShader ()
: Shader(GL_GEOMETRY_SHADER) {}

/**
 * Constructor taking in the geometry shader source code as a std::string.
 *
 * @param source geometry shader source code
 */
tw::GeometryShader::GeometryShader (const std::string& source)
: Shader(GL_GEOMETRY_SHADER, source) {

    compile();

}
