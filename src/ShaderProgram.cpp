#include "../include/ShaderProgram.hpp"

/**
 * @class tw::ShaderProgram
 *
 * Handle for an OpenGL shader program (version 2.0+), linking together various
 * shader types to be executed by the renderer.
 */

tw::ShaderProgram::ShaderProgram () {

    m_id = glCreateProgram();

}

tw::ShaderProgram::ShaderProgram (
    const std::shared_ptr<VertexShader>& vertexShader,
    const std::shared_ptr<FragmentShader>& fragmentShader,
    const std::shared_ptr<GeometryShader>& geometryShader,
    const std::shared_ptr<TesselationEvaluationShader>& tesselationEvaluationShader,
    const std::shared_ptr<TesselationControlShader>& tesselationControlShader,
    const std::shared_ptr<ComputeShader>& computeShader
)
:   m_vertexShader(vertexShader),
    m_fragmentShader(fragmentShader),
    m_geometryShader(geometryShader),
    m_tesselationEvaluationShader(tesselationEvaluationShader),
    m_tesselationControlShader(tesselationControlShader),
    m_computeShader(computeShader)
{

    m_id = glCreateProgram();
    link();

}

GLuint tw::ShaderProgram::getId () const {

    return m_id;

}

bool tw::ShaderProgram::isLinked () const {

    return m_linked;

}

std::shared_ptr<tw::VertexShader> tw::ShaderProgram::getVertexShader () const {

    return m_vertexShader;

}

std::shared_ptr<tw::FragmentShader> tw::ShaderProgram::getFragmentShader () const {

    return m_fragmentShader;

}

std::shared_ptr<tw::GeometryShader> tw::ShaderProgram::getGeometryShader () const {

    return m_geometryShader;

}

std::shared_ptr<tw::TesselationEvaluationShader> tw::ShaderProgram::getTesselationEvaluationShader () const {

    return m_tesselationEvaluationShader;

}

std::shared_ptr<tw::TesselationControlShader> tw::ShaderProgram::getTesselationControlShader () const {

    return m_tesselationControlShader;

}

std::shared_ptr<tw::ComputeShader> tw::ShaderProgram::getComputeShader () const {

    return m_computeShader;

}

bool tw::ShaderProgram::setVertexShader (const std::shared_ptr<VertexShader>& vertexShader) {

    if (isLinked()) {
        return false;
    }

    m_vertexShader = vertexShader;

    return true;

}

bool tw::ShaderProgram::setFragmentShader (const std::shared_ptr<FragmentShader>& fragmentShader) {

    if (isLinked()) {
        return false;
    }

    m_fragmentShader = fragmentShader;

    return true;

}

bool tw::ShaderProgram::setGeometryShader (const std::shared_ptr<GeometryShader>& geometryShader) {

    if (isLinked()) {
        return false;
    }

    m_geometryShader = geometryShader;

    return true;

}

bool tw::ShaderProgram::setTesselationEvaluationShader (const std::shared_ptr<TesselationEvaluationShader>& tesselationEvaluationShader) {

    if (isLinked()) {
        return false;
    }

    m_tesselationEvaluationShader = tesselationEvaluationShader;

    return true;

}

bool tw::ShaderProgram::setTesselationControlShader (const std::shared_ptr<TesselationControlShader>& tesselationControlShader) {

    if (isLinked()) {
        return false;
    }

    m_tesselationControlShader = tesselationControlShader;

    return true;

}

bool tw::ShaderProgram::setComputeShader (const std::shared_ptr<ComputeShader>& computeShader) {

    if (isLinked()) {
        return false;
    }

    m_computeShader = computeShader;

    return true;

}

bool tw::ShaderProgram::link () {

    if (m_vertexShader != nullptr) {
        glAttachShader(m_id, m_vertexShader->getId());
    }

    if (m_fragmentShader != nullptr) {
        glAttachShader(m_id, m_fragmentShader->getId());
    }

    if (m_geometryShader != nullptr) {
        glAttachShader(m_id, m_geometryShader->getId());
    }

    if (m_tesselationEvaluationShader != nullptr) {
        glAttachShader(m_id, m_tesselationEvaluationShader->getId());
    }

    if (m_tesselationControlShader != nullptr) {
        glAttachShader(m_id, m_tesselationControlShader->getId());
    }

    if (m_computeShader != nullptr) {
        glAttachShader(m_id, m_computeShader->getId());
    }

    glLinkProgram(m_id);

    GLint linkStatus;
    glGetProgramiv(m_id, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE) {

        GLsizei infoLogLength;
        std::array<GLchar, 255> infoLog;
        std::string infoLogString;
        glGetProgramInfoLog(m_id, 255, &infoLogLength, infoLog.data());
        infoLogString.reserve(infoLogLength);
        for (unsigned int i = 0; i < infoLogLength; ++i) {
            infoLogString += infoLog.at(i);
        }
        Log::error("opengl", "OpenGL shader program link error: ", infoLogString);

        return false;

    }

    m_linked = true;
    return true;

}

bool tw::ShaderProgram::use () {

    if (!isLinked()) {
        if (!link()) {
            return false;
        }
    }

    glUseProgram(m_id);

    return true;

}

bool tw::ShaderProgram::unuse () {

    glUseProgram(0);

    return true;

}
