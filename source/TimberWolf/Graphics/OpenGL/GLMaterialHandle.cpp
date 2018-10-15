#include "../../../../include/TimberWolf/Graphics/OpenGL/GLMaterialHandle.hpp"

tw::GLMaterialHandle::GLMaterialHandle (GLShaderProgram&& shaderProgram)
: m_shaderProgram(std::move(shaderProgram)) {}

tw::GLMaterialHandle::GLMaterialHandle (Material& material) {

    init();

    // TODO: impart the material variables to the shaders, probably via uniforms

}

bool tw::GLMaterialHandle::bind () {

    m_shaderProgram.bind();
    return true;

}

bool tw::GLMaterialHandle::unbind () {

    GLShaderProgram::clearBound();
    return true;

}

bool tw::GLMaterialHandle::clearBound () {

    GLShaderProgram::clearBound ();
    return true;

}

void tw::GLMaterialHandle::init () {

    std::shared_ptr<GLVertexShader> vert;
    std::shared_ptr<GLFragmentShader> frag;

    if (m_vert.expired()) {

        vert = std::make_shared<GLVertexShader>();
        m_vert = vert; // save a weak copy
        vert->setSource("#version 330 core"
            "layout (location=0) in vec3 vertexPosition_modelspace;"

            "void main () {"
                "gl_Position.xyz = vertexPosition_modelspace;"
                "gl_Position.w = 1.0;"
            "}");
        vert->compile();

    } else {

        // get existing copy
        std::shared_ptr<GLVertexShader> vert = std::shared_ptr<GLVertexShader>(m_vert);

    }

    if (m_frag.expired()) {

        frag = std::make_unique<GLFragmentShader>();
        m_frag = frag; // save a weak copy
        frag->setSource("#version 330 core"
            "layout (location=0) out vec4 color;"

            "void main () {"
                "color = vec4(1.0, 0.0, 0.0, 1.0);"
            "}");
        frag->compile();

    }

    m_shaderProgram.setVertexShader(vert);
    m_shaderProgram.setFragmentShader(frag);

    m_shaderProgram.link();

}

std::weak_ptr<tw::GLVertexShader> tw::GLMaterialHandle::m_vert {};
std::weak_ptr<tw::GLFragmentShader> tw::GLMaterialHandle::m_frag {};
