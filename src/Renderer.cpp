#include "../include/Renderer.hpp"

void tw::Renderer::render (const Model& model) {

    auto vao = model.getVAO();

    vao->bind();
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());

    glDisableVertexAttribArray(0);
    vao->unbind();

}
