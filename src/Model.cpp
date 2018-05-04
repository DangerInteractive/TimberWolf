#include "../include/Model.hpp"

tw::Model::Model (VertexArray&& vao)
: m_vao(std::make_shared<VertexArray>(std::move(vao))) {}

tw::Model::Model (const std::shared_ptr<VertexArray>& vao)
: m_vao(vao) {}

tw::Model::Model (VertexArray&& vao, const std::shared_ptr<ShaderProgram>& shader)
: m_vao(std::make_shared<VertexArray>(std::move(vao))), m_shader(shader) {}

tw::Model::Model (VertexArray&& vao, const std::string& shader)
: m_vao(std::make_shared<VertexArray>(std::move(vao))), m_shader(ShaderStore::getShaderProgram(shader)) {}

tw::Model::Model (const std::shared_ptr<VertexArray>& vao, const std::shared_ptr<ShaderProgram>& shader)
: m_vao(vao), m_shader(shader) {}

tw::Model::Model (const std::shared_ptr<VertexArray>& vao, const std::string& shader)
: m_vao(vao), m_shader(ShaderStore::getShaderProgram(shader)) {}

std::shared_ptr<tw::VertexArray> tw::Model::getVAO () const {

    return m_vao;

}

std::shared_ptr<tw::ShaderProgram> tw::Model::getShaderProgram () const {

    return m_shader;

}

unsigned int tw::Model::getVertexCount () const {

    return m_vertexCount;

}

void tw::Model::setVAO (VertexArray&& vao) {

    m_vao = std::make_shared<VertexArray>(std::move(vao));

}

void tw::Model::setVAO (const std::shared_ptr<VertexArray>& vao) {

    m_vao = vao;

}

void tw::Model::setShaderProgram (const std::shared_ptr<ShaderProgram>& shader) {

    m_shader = shader;

}

void tw::Model::setShaderProgram (const std::string& shader) {

    m_shader = ShaderStore::getShaderProgram(shader);

}

void tw::Model::setVertexCount (unsigned int vertexCount) {

    m_vertexCount = vertexCount;

}
