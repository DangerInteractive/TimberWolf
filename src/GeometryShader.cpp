#include "../include/GeometryShader.hpp"

/**
 * @class tw::GeometryShader
 *
 * Handle for an OpenGL geometry shader (version 3.2+).
 */

tw::GeometryShader::GeometryShader ()
: Shader(GL_GEOMETRY_SHADER) {}

tw::GeometryShader::GeometryShader (const std::string& source)
: Shader(GL_GEOMETRY_SHADER, source) {

    compile();

}
