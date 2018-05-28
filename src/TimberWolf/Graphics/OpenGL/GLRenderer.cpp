#include "../../../../include/TimberWolf/Graphics/OpenGL/GLRenderer.hpp"

/**
 * @class tw::GLRenderer
 *
 * Static class to which tw::Model objects are passed to be rendered via OpenGL
 * to the game window.
 */

void tw::GLRenderer::render (const Scene*) {

    // TODO: implement OpenGL rendering of Scenes

}

/**
 * Render a tw::Model object with OpenGL to the window.
 *
 * @param model model to render
 */
void tw::GLRenderer::render (const Model* model) {

    // TODO: relegate this to a protected method rendering objects in the world
    auto vao = model->getVAO();

    vao->bind();
    glEnableVertexAttribArray(0);

    if (model->getShaderProgram() != nullptr) {
        model->getShaderProgram()->use();
    }

    glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount());

    GLShaderProgram::unuse();
    glDisableVertexAttribArray(0);
    vao->unbind();

}

void tw::GLRenderer::clearColor (const Color& color) {

    if (m_lastClearColor != color) {
        glClearColor(
            color.getR(),
            color.getG(),
            color.getB(),
            color.getA()
        );
        m_lastClearColor = color;
    }
    glClear(GL_COLOR_BUFFER_BIT);

}

void tw::GLRenderer::clearColor () {

    auto defaultClearColor = getDefaultClearColor();

    if (m_lastClearColor != defaultClearColor) {
        glClearColor(
            defaultClearColor.getR(),
            defaultClearColor.getG(),
            defaultClearColor.getB(),
            defaultClearColor.getA()
        );
        m_lastClearColor = defaultClearColor;
    }
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
