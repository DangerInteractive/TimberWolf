#include "../include/Shader.hpp"

tw::Shader::~Shader () {

    glDeleteShader(m_id);

}

GLenum tw::Shader::getType () const {

    return m_type;

}

GLuint tw::Shader::getId () const {

    return m_id;

}

std::string tw::Shader::getSource () const {

    return m_source;

}

bool tw::Shader::isCompiled () const {

    return m_compiled;

}

bool tw::Shader::setSource (const std::string& source) {

    if (isCompiled()) {
        return false;
    }

    m_source = source;

    return true;

}

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

tw::Shader::Shader (GLenum type)
: m_type(type) {

    m_id = glCreateShader(type);

};

tw::Shader::Shader (GLenum type, const std::string& source)
: m_type(type), m_source(source) {

    m_id = glCreateShader(type);

};
