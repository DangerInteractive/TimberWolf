#include "../include/Shader.hpp"

/**
 * @class tw::Shader
 *
 * Abstract class representing a generic shader. This class should not be
 * instantiated on its own, it should instead be stored polymorphically and
 * instantiated as a tw::VertexShader, tw::FragmentShader, tw::GeometryShader,
 * tw::TesselationEvaluationShader, tw::TesselationControlShader, or
 * tw::ComputeShader.
 */

/**
 * Destructor. Removes the shader from OpenGL and frees the associated GPU
 * memory.
 */
tw::Shader::~Shader () {

    glDeleteShader(m_id);

}

/**
 * Get the GLenum of the shader type.
 *
 * @return shader type enumeration
 */
GLenum tw::Shader::getType () const {

    return m_type;

}

/**
 * Get the ID of the shader.
 *
 * @return shader ID
 */
GLuint tw::Shader::getId () const {

    return m_id;

}

/**
 * Get the source code of the shader as a std::string.
 *
 * @return shader source code
 */
std::string tw::Shader::getSource () const {

    return m_source;

}

/**
 * Check if the shader has been compiled.
 *
 * @return true if the shader has been compiled, false if not
 */
bool tw::Shader::isCompiled () const {

    return m_compiled;

}

/**
 * Set the source code of a shader program to a given std::string.
 *
 * @param source shader source code
 */
bool tw::Shader::setSource (const std::string& source) {

    if (isCompiled()) {
        return false;
    }

    m_source = source;

    auto cSource = m_source.c_str();
    GLint sourceSize = m_source.size();
    glShaderSource(m_id, 1, &cSource, &sourceSize);

    return true;

}

/**
 * Compile the shader.
 *
 * @return true if the shader is successfully compiled, false if not
 */
bool tw::Shader::compile () {

    if (isCompiled()) {
        return true;
    }

    if (m_id == 0) {
        return false;
    }

    glCompileShader(m_id);

    GLint compileStatus;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus != GL_TRUE) {

        GLsizei infoLogLength;
        std::array<GLchar, 255> infoLog;
        std::string infoLogString;
        glGetShaderInfoLog(m_id, 255, &infoLogLength, &infoLog[0]);
        infoLogString.reserve(infoLogLength);
        for (unsigned int i = 0; i < infoLogLength; ++i) {
            infoLogString.push_back(infoLog[i]);
        }
        Log::error("opengl", "OpenGL shader compile error: ", infoLogString);

        return false;

    }

    m_compiled = true;
    return true;

}

/**
 * Constructor taking in a GLenum shader type. This constructor is called by the
 * default constructors of tw::VertexShader, tw::FragmentShader,
 * tw::GeometryShader, tw::TesselationEvaluationShader,
 * tw::TesselationControlShader, and tw::ComputeShader.
 *
 * @param type shader type enumeration
 */
tw::Shader::Shader (GLenum type)
: m_type(type) {

    m_id = glCreateShader(type);

};

/**
 * Constructor taking in a GLenum shader type and a std::string of shader source
 * code. This constructor is called by the source code constructors of
 * tw::VertexShader, tw::FragmentShader, tw::GeometryShader,
 * tw::TesselationEvaluationShader, tw::TesselationControlShader,
 * and tw::ComputeShader.
 *
 * @param type   shader type enumeration
 * @param source shader source code
 */
tw::Shader::Shader (GLenum type, const std::string& source)
: m_type(type) {

    m_id = glCreateShader(type);

    setSource(source);

};
