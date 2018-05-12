#include "../include/ShaderProgram.hpp"

/**
 * @class tw::ShaderProgram
 *
 * Handle for an OpenGL shader program (version 2.0+), linking together various
 * shader types to be executed by the renderer.
 */

/**
 * Default constructor. Allocates OpenGL shader program resource on GPU.
 */
tw::ShaderProgram::ShaderProgram () {

    m_id = glCreateProgram();

}

/**
 * Constructor taking in optional std::shared_ptrs to one of each handle: vertex
 * shader, fragment shader, geometry shader, tesselation evaluation shader,
 * tesselation control shader, compute shader.
 *
 * @param vertexShader                vertex shader handle (optional) (pass nullptr to disable)
 * @param fragmentShader              fragment shader handle (optional) (pass nullptr to disable)
 * @param geometryShader              geometry shader handle (optional) (pass nullptr to disable)
 * @param tesselationEvaluationShader tesselation evaluation shader handle (optional) (pass nullptr to disable)
 * @param tesselationControlShader    tesselation control shader handle (optional) (pass nullptr to disable)
 * @param computeShader               conpute shader handle (optional) (pass nullptr to disable)
 */
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

/**
 * Get the ID of the shader program.
 *
 * @return shader program ID
 */
GLuint tw::ShaderProgram::getId () const {

    return m_id;

}

/**
 * Check if the shader program has been linked.
 *
 * @return true if the shader program has been linked, false if not
 */
bool tw::ShaderProgram::isLinked () const {

    return m_linked;

}

/**
 * Get a std::shared_ptr to the attached vertex shader. If no vertex shader is
 * attached, returns nullptr.
 *
 * @return shared pointer to attached vertex shader, or nullptr if none
 */
std::shared_ptr<tw::VertexShader> tw::ShaderProgram::getVertexShader () const {

    return m_vertexShader;

}

/**
 * Get a std::shared_ptr to the attached fragment shader. If no fragment shader
 * is attached, returns nullptr.
 *
 * @return shared pointer to attached fragment shader, or nullptr if none
 */
std::shared_ptr<tw::FragmentShader> tw::ShaderProgram::getFragmentShader () const {

    return m_fragmentShader;

}

/**
 * Get a std::shared_ptr to the attached geometry shader. If no geometry shader
 * is attached, returns nullptr.
 *
 * @return shared pointer to attached geometry shader, or nullptr if none
 */
std::shared_ptr<tw::GeometryShader> tw::ShaderProgram::getGeometryShader () const {

    return m_geometryShader;

}

/**
 * Get a std::shared_ptr to the attached tesselation evaluation shader. If no
 * tesselation evaluation shader is attached, returns nullptr.
 *
 * @return shared pointer to attached tesselation evaluation shader, or nullptr if none
 */
std::shared_ptr<tw::TesselationEvaluationShader> tw::ShaderProgram::getTesselationEvaluationShader () const {

    return m_tesselationEvaluationShader;

}

/**
 * Get a std::shared_ptr to the attached tesselation control shader. If no
 * tesselation control shader is attached, returns nullptr.
 *
 * @return shared pointer to attached tesselation control shader, or nullptr if none
 */
std::shared_ptr<tw::TesselationControlShader> tw::ShaderProgram::getTesselationControlShader () const {

    return m_tesselationControlShader;

}

/**
 * Get a std::shared_ptr to the attached compute shader. If no compute shader is
 * attached, returns nullptr.
 *
 * @return shared pointer to attached compute shader, or nullptr if none
 */
std::shared_ptr<tw::ComputeShader> tw::ShaderProgram::getComputeShader () const {

    return m_computeShader;

}

/**
 * Set the attached vertex shader to a given std::shared_ptr to a vertex shader
 * handle. Only works if the program has not already been linked. You can pass
 * nullptr to unset the vertex shader.
 *
 * @param vertexShader shared pointer to vertex shader handle
 * @return true if vertex shader was successfully set, false if not
 */
bool tw::ShaderProgram::setVertexShader (const std::shared_ptr<VertexShader>& vertexShader) {

    if (isLinked()) {
        return false;
    }

    m_vertexShader = vertexShader;

    return true;

}

/**
 * Set the attached fragment shader to a given std::shared_ptr to a fragment
 * shader handle. Only works if the program has not already been linked. You can
 * pass nullptr to unset the fragment shader.
 *
 * @param fragmentShader shared pointer to fragment shader handle
 * @return true if fragment shader was successfully set, false if not
 */
bool tw::ShaderProgram::setFragmentShader (const std::shared_ptr<FragmentShader>& fragmentShader) {

    if (isLinked()) {
        return false;
    }

    m_fragmentShader = fragmentShader;

    return true;

}

/**
 * Set the attached geometry shader to a given std::shared_ptr to a geometry
 * shader handle. Only works if the program has not already been linked. You can
 * pass nullptr to unset the geometry shader.
 *
 * @param geometryShader shared pointer to geometry shader handle
 * @return true if geometry shader was successfully set, false if not
 */
bool tw::ShaderProgram::setGeometryShader (const std::shared_ptr<GeometryShader>& geometryShader) {

    if (isLinked()) {
        return false;
    }

    m_geometryShader = geometryShader;

    return true;

}

/**
 * Set the attached tesselation evaluation shader to a given std::shared_ptr to
 * a tesselation evaluation shader handle. Only works if the program has not
 * already been linked. You can pass nullptr to unset the tesselation
 * evaluation shader.
 *
 * @param tesselationEvaluationShader shared pointer to tesselation evaluation shader handle
 * @return true if tesselation evaluation shader was successfully set, false if not
 */
bool tw::ShaderProgram::setTesselationEvaluationShader (const std::shared_ptr<TesselationEvaluationShader>& tesselationEvaluationShader) {

    if (isLinked()) {
        return false;
    }

    m_tesselationEvaluationShader = tesselationEvaluationShader;

    return true;

}

/**
 * Set the attached tesselation control shader to a given std::shared_ptr to a
 * tesselation control shader handle. Only works if the program has not already
 * been linked. You can pass nullptr to unset the tesselation control shader.
 *
 * @param tesselationControlShader shared pointer to tesselation control shader handle
 * @return true if tesselation control shader was successfully set, false if not
 */
bool tw::ShaderProgram::setTesselationControlShader (const std::shared_ptr<TesselationControlShader>& tesselationControlShader) {

    if (isLinked()) {
        return false;
    }

    m_tesselationControlShader = tesselationControlShader;

    return true;

}

/**
 * Set the attached compute shader to a given std::shared_ptr to a compute
 * shader handle. Only works if the program has not already been linked. You can
 * pass nullptr to unset the compute shader.
 *
 * @param computeShader shared pointer to compute shader handle
 * @return true if compute shader was successfully set, false if not
 */
bool tw::ShaderProgram::setComputeShader (const std::shared_ptr<ComputeShader>& computeShader) {

    if (isLinked()) {
        return false;
    }

    m_computeShader = computeShader;

    return true;

}

/**
 * Link all of the attached shaders in the shader program. Once this is done,
 * the attached shaders cannot be modified.
 */
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

/**
 * Set the shader program as the current program for use in rendering.
 *
 * @return true if shader program was successfully activated, false if not
 */
bool tw::ShaderProgram::use () {

    if (!isLinked()) {
        if (!link()) {
            return false;
        }
    }

    glUseProgram(m_id);

    return true;

}

/**
 * Disable the active shader program, equivalent to binding no shader.
 *
 * @return true if shader was successfully deactivated, false if not
 */
bool tw::ShaderProgram::unuse () {

    glUseProgram(0);

    return true;

}
