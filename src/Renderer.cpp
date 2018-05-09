#include "../include/Renderer.hpp"

/**
 * @class tw::Renderer
 *
 * Static class to which tw::Model objects are passed to be rendered via OpenGL
 * to the game window.
 */

void tw::Renderer::render (const Model& model) {

    auto vao = model.getVAO();

    vao->bind();
    glEnableVertexAttribArray(0);

    if (model.getShaderProgram() != nullptr) {
        model.getShaderProgram()->use();
    }

    glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());

    ShaderProgram::unuse();
    glDisableVertexAttribArray(0);
    vao->unbind();

}
