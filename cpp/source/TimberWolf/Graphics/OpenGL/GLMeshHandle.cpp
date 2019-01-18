#include "../../../../include/TimberWolf/Graphics/OpenGL/GLMeshHandle.hpp"

tw::GLMeshHandle::GLMeshHandle (GLVertexArray&& vao)
: m_vao(std::move(vao)) {}

tw::GLMeshHandle::GLMeshHandle (Mesh& mesh) {

    m_vao.buffer(&mesh);

}

const tw::GLVertexArray& tw::GLMeshHandle::getVao () const {

    return m_vao;

}

bool tw::GLMeshHandle::bind () {

    m_vao.bind();
    return true;

}

bool tw::GLMeshHandle::unbind () {

    return clearBound();

}

bool tw::GLMeshHandle::clearBound () {

    GLVertexArray::unbind();
    return true;

}
