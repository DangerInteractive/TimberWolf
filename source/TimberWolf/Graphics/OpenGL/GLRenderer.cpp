#include "../../../../include/TimberWolf/Graphics/OpenGL/GLRenderer.hpp"

/**
 * @class tw::GLRenderer
 *
 * Static class to which tw::Model objects are passed to be rendered via OpenGL
 * to the game window.
 */

std::shared_ptr<tw::MaterialHandle> tw::GLRenderer::put (const Material& material) {

    // TODO: actually do something useful here, instead of placeholder code
    return std::static_pointer_cast<MaterialHandle>(std::make_shared<GLShaderProgram>());

}

std::shared_ptr<tw::MeshHandle> tw::GLRenderer::put (const Mesh& mesh) {

    // TODO: actually do something useful here, instead of placeholder code
    return std::static_pointer_cast<MeshHandle>(std::make_shared<GLVertexArray>());

}

void tw::GLRenderer::render (const Scene* scene) {

    // TODO: OpenGL specific scene setup here?

    Renderer::render(scene);

}

void tw::GLRenderer::render (const Puppet* puppet) {

    // TODO

}

void tw::GLRenderer::clear () {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void tw::GLRenderer::clearColor () {

    glClear(GL_COLOR_BUFFER_BIT);

}

void tw::GLRenderer::clearDepth () {

    glClear(GL_DEPTH_BUFFER_BIT);

}

void tw::GLRenderer::onWindowOpen () {

    Window::makeContextCurrent();

    GLenum glewStatus = glewInit();

    if (glewStatus != GLEW_OK) {
        Log::error(
            "GLEW Error: ",
            glewGetErrorString(glewStatus)
        );
    }

    if (Window::getGlVersionMajor() > 4 || (Window::getGlVersionMajor() == 4 && Window::getGlVersionMinor() >= 3)) {
        glDebugMessageCallback(glLiveDebug, nullptr);
    }

}

void tw::GLRenderer::onWindowClose () {

    return;

}

void tw::GLRenderer::setClearColor (const Color& color) {

    glClearColor(color.getR(), color.getG(), color.getB(), color.getA());
    Renderer::setClearColor(color);

}

/**
 * Render a tw::Model object with OpenGL to the window.
 *
 * @param model model to render
 */
void tw::GLRenderer::drawModel (const Model* model) {

    auto vao = model->getVAO();

    vao->bind();
    glEnableVertexAttribArray(0);

    if (model->getShaderProgram() != nullptr) {
        model->getShaderProgram()->bind();
    }

    glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount());

    GLShaderProgram::clearBound();
    glDisableVertexAttribArray(0);
    vao->unbind();

}

/**
 * Callback for OpenGL errors, which functions only for OpenGL 4.3+. This is a
 * major improvement in OpenGL error logging, as it does not require a costly
 * request for logged error messages, and messages are logged instantly.
 *
 * @param source    source of the OpenGL error
 * @param type      type of the OpenGL error
 * @param id        ID of the OpenGL error
 * @param severity  severity of the OpenGL error
 * @param length    length of the message
 * @param message   message text
 * @param userParam user parameter passed during binding (should be nullptr)
 */
void tw::GLRenderer::glLiveDebug (
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam
) {

    std::string messageString;
    messageString.reserve(length);
    for (int i = 0; i < length; ++i) {
        messageString += message[i];
    }

    Log::error(
        "opengl",
        "OpenGL Error: ", messageString,
        " source: ", source,
        " type: ", type,
        " id: ", id,
        " severity: ", severity
    );

}
