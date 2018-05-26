#include "../../../include/TimberWolf/Graphics/Model.hpp"

/**
 * @class tw::Model
 *
 * Representation of a three dimensional model, to be rendered by tw::Renderer.
 * It stores a handle to an OpenGL VAO (vertex array object) containing the
 * vertex, index, and texture buffers, a count of vertices in the VAO, and a
 * handle to an OpenGL shader program to use while the object is being rendered.
 */

/**
 * Constructor taking in an rvalue to a handle to a vertex array object. (VAO
 * handles cannot be copied, so it cannot be an lvalue).
 *
 * @param vao rvalue vertex array object handle
 */
tw::Model::Model (GLVertexArray&& vao)
: m_vao(std::make_shared<GLVertexArray>(std::move(vao))) {}

/**
 * Constructor taking in a std::shared_ptr to a handle to a vertex array object.
 *
 * @param vao shared pointer to a vertex array object handle
 */
tw::Model::Model (const std::shared_ptr<GLVertexArray>& vao)
: m_vao(vao) {}

/**
 * Constructor taking in an rvalue to a handle to a vertex array objet and a
 * std::shared_ptr to a handle to a shader program.
 *
 * @param vao    rvalue vertex array object handle
 * @param shader shared pointer to a shader program
 */
tw::Model::Model (GLVertexArray&& vao, const std::shared_ptr<GLShaderProgram>& shader)
: m_vao(std::make_shared<GLVertexArray>(std::move(vao))), m_shader(shader) {}

/**
 * Constructor taking in an rvalue to a handle to a vertex array object and a
 * std::string key to a shader program handle stored in tw::GLShaderStore.
 *
 * @param vao    rvalue vertex array object handle
 * @param shader shader program key
 */
tw::Model::Model (GLVertexArray&& vao, const std::string& shader)
: m_vao(std::make_shared<GLVertexArray>(std::move(vao))), m_shader(GLShaderStore::getShaderProgram(shader)) {}

/**
 * Constructor taking in a std::shared_ptr to a handle to a vertex array object
 * and a std::shared_ptr to a handle to a shader program.
 *
 * @param vao    shared pointer to a vertex array object handle
 * @param shader shared pointer to a shader program handle
 */
tw::Model::Model (const std::shared_ptr<GLVertexArray>& vao, const std::shared_ptr<GLShaderProgram>& shader)
: m_vao(vao), m_shader(shader) {}

/**
 * Constructor taking in a std::shared_ptr to a handle to a vertex array object
 * and a std::string key to a handle to a shader program stored in
 * tw::GLShaderStore.
 *
 * @param vao    shared pointer to a vertex array object handle
 * @param shader key to a shader program handle
 */
tw::Model::Model (const std::shared_ptr<GLVertexArray>& vao, const std::string& shader)
: m_vao(vao), m_shader(GLShaderStore::getShaderProgram(shader)) {}

/**
 * Get a std::shared_ptr to the vertex array object handle.
 *
 * @return shared pointer to the vertex array object handle
 */
std::shared_ptr<tw::GLVertexArray> tw::Model::getVAO () const {

    return m_vao;

}

/**
 * Get a std::shared_ptr to the shader program handle.
 *
 * @return shared pointer to the shared pointer handle
 */
std::shared_ptr<tw::GLShaderProgram> tw::Model::getShaderProgram () const {

    return m_shader;

}

/**
 * Get the count of vertices.
 *
 * @return vertex count
 */
unsigned int tw::Model::getVertexCount () const {

    return m_vertexCount;

}

/**
 * Set the vertex array object handle to a given rvalue to a vertex array object
 * handle (VAO handles cannot be copied, so it must be an rvalue).
 *
 * @param vao rvalue to vertex array object handle
 */
void tw::Model::setVAO (GLVertexArray&& vao) {

    m_vao = std::make_shared<GLVertexArray>(std::move(vao));

}

/**
 * Set the vertex array object handle to a given std::shared_ptr to a vertex
 * array object handle.
 *
 * @param vao shared pointer to vertex array object handle
 */
void tw::Model::setVAO (const std::shared_ptr<GLVertexArray>& vao) {

    m_vao = vao;

}

/**
 * Set the shader program handle to a given std::shared_ptr to a shader program
 * handle.
 *
 * @param shader shared pointer to shader program handle
 */
void tw::Model::setShaderProgram (const std::shared_ptr<GLShaderProgram>& shader) {

    m_shader = shader;

}

/**
 * Set the shader program handle to a given std::string key to a shader program
 * handle stored in tw::GLShaderStore.
 *
 * @param shader key to a shader program handle
 */
void tw::Model::setShaderProgram (const std::string& shader) {

    m_shader = GLShaderStore::getShaderProgram(shader);

}

/**
 * Set the count of vertices.
 *
 * @param vertexCount vertex count
 */
void tw::Model::setVertexCount (unsigned int vertexCount) {

    m_vertexCount = vertexCount;

}
