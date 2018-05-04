#include "../include/Model.hpp"

tw::Model::Model (VertexArray&& vao)
: m_vao(std::make_shared<VertexArray>(std::move(vao))) {}

tw::Model::Model (const std::shared_ptr<VertexArray>& vao)
: m_vao(vao) {}

std::shared_ptr<tw::VertexArray> tw::Model::getVAO () const {

    return m_vao;

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

void tw::Model::setVertexCount (unsigned int vertexCount) {

    m_vertexCount = vertexCount;

}
