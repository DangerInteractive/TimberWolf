#include "../../../include/TimberWolf/Window/Window.hpp"

/**
 * @class tw::Window
 *
 * Static class keeping track of the GLFW window handle and allowing access and
 * manipulation to window properties.
 */

/**
 * Initialize the window. This must be done before opening the window. It
 * binds error handlers and makes sure GLFW and OpenGL are ready and available.
 */
void tw::Window::init () {

    glfwSetErrorCallback([](int error, const char* description){

        Log::error("window",
            std::showbase,
            std::internal,
            std::setfill('0'),
            "GLFW Error: ",
            std::dec, error, ' ',
            std::hex, std::setw(10), ERROR, ": ", std::dec,
            description
        );

    });

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    Log::verbose("window", "GLFW initialized.");

}

/**
 * Deinitialize the window. This must only be done after closing the window,
 * and it cleans up GLFW and OpenGL resources. This is meant to be called only
 * prior to terminating the program.
 */
void tw::Window::deinit () {

    glfwTerminate();

    Log::verbose("window", "GLFW terminated.");

}

/**
 * Get a pointer to the GLFW window context, if available, or nullptr otherwise.
 *
 * @return pointer to the GLFW window context, or nullptr if not available
 */
GLFWwindow* tw::Window::getContext () {

    return m_context.get();

}

/**
 * Make the window context current. This should be done prior to drawing to the
 * window, as this informs OpenGL to draw to this window.
 */
void tw::Window::makeContextCurrent () {

    if (m_context != NULL) {
        glfwMakeContextCurrent(m_context.get());
        Log::verbose("window", "Set GLFW window as current context.");
    } else {
        throw std::runtime_error("Cannot set NULL context current.");
    }

}

/**
 * Check if the window is open.
 *
 * @return true if the window is open, false if not
 */
bool tw::Window::isOpen () {

    return m_context != nullptr;

}

/**
 * Open the window. This should be done after calling tw::Window::init.
 */
void tw::Window::open () {

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_glVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_glVersionMinor);

    m_context = std::unique_ptr<GLFWwindow, GLFWwindowDeleter>(glfwCreateWindow(
        m_width,
        m_height,
        m_title.c_str(),
        NULL,
        NULL
    ));

    if (!m_context) {
        glfwTerminate();
        Log::error("window", "Failed to get a window or OpenGL context.");
    }

    makeContextCurrent();

    glfwSwapInterval(1);

    GLenum glewStatus = glewInit();

    if (glewStatus != GLEW_OK) {
        Log::error(
            "GLEW Error: ",
            glewGetErrorString(glewStatus)
        );
    }

    if (m_glVersionMajor >= 4 && m_glVersionMinor >= 3) {
        glDebugMessageCallback(glLiveDebug, nullptr);
    }

    Log::verbose("window", "GLEW initialized.");

}

/**
 * Close the window. This should be done before calling tw::Window::destroy.
 */
void tw::Window::close () {

    if (isOpen()) {
        glfwSetWindowShouldClose(m_context.get(), 1);
    }

}

/**
 * Destroy the window context. This should be done after calling
 * tw::Window::close and before calling tw::Window::deinit.
 */
void tw::Window::destroy () {

    if (isOpen()) {
        m_context.reset();
    }

}

/**
 * Clear the window between draws.
 */
void tw::Window::clear () {

    if (isOpen()) {
        if (m_lastClearColor != m_defaultClearColor) {
            glClearColor(
                m_defaultClearColor.getR(),
                m_defaultClearColor.getG(),
                m_defaultClearColor.getB(),
                m_defaultClearColor.getA()
            );
            m_lastClearColor = m_defaultClearColor;
        }
        glClear(GL_COLOR_BUFFER_BIT);
    }

}

/**
 * Clear the window between draws, given a clear color.
 *
 * @param color clear color
 */
void tw::Window::clear (const Color& color) {

    if (isOpen()) {
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

}

/**
 * Clear the window between draws, given a clear color as red, green, blue, and
 * alpha channels, respectively.
 *
 * @param r normalized value for red channel (0-1)
 * @param g normalized value for green channel (0-1)
 * @param b normalized value for blue channel (0-1)
 * @param a normalized value for alpha channel (0-1)
 */
void tw::Window::clear (float r, float g, float b, float a) {

    if (isOpen()) {

        Color color {r, g, b, a};

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

}

/**
 * Get the width of the window in pixels.
 *
 * @return width of window in pixels
 */
int tw::Window::getWidth () {

    return m_width;

}

/**
 * Get the height of the window in pixels.
 *
 * @return height of window in pixels
 */
int tw::Window::getHeight () {

    return m_height;

}

/**
 * Set the width of the window in pixels.
 *
 * @param new width of window in pixels
 */
void tw::Window::setWidth (const int width) {

    std::unique_lock<std::mutex> lock_size(mutex_size);

    m_width = width;
    pushWindowSize();

}

/**
 * Set the height of the window in pixels.
 *
 * @param height new height of the window in pixels
 */
void tw::Window::setHeight (const int height) {

    std::unique_lock<std::mutex> lock_size(mutex_size);

    m_height = height;
    pushWindowSize();

}

/**
 * Set the size of the window, given the width and height of the window in
 * pixels, respectively.
 *
 * @param width  new width of the window
 * @param height new height of the window
 */
void tw::Window::setSize (const int width, const int height) {

    std::unique_lock<std::mutex> lock_size(mutex_size);

    m_width = width;
    m_height = height;
    pushWindowSize();

}

/**
 * Get the title of the window.
 *
 * @return window title
 */
std::string tw::Window::getTitle () {

    return m_title;

}

/**
 * Set the title of the window. This is what is shown in the OS window's title
 * bar.
 *
 * @param title new window title
 */
void tw::Window::setTitle (const std::string& title) {

    std::unique_lock<std::mutex> lock_title(mutex_title);

    m_title = title;
    pushWindowTitle();

}

/**
 * Get the major version of the OpenGL context for the window.
 *
 * @return OpenGL major version of context
 */
int tw::Window::getGlVersionMajor () {

    return m_glVersionMajor;

}

/**
 * Get the minor version of the OpenGL context for the window.
 *
 * @return OpenGL minor version of context
 */
int tw::Window::getGlVersionMinor () {

    return m_glVersionMinor;

}

/**
 * Get the version of OpenGL as a std::string.
 *
 * @return OpenGL version string of context
 */
std::string tw::Window::getGlVersion () {

    std::ostringstream oss;
    oss << m_glVersionMajor << '.' << m_glVersionMinor;
    return oss.str();

}

/**
 * Set the major version of the OpenGL context.
 *
 * @param majorVersion new OpenGL major version of the context
 */
void tw::Window::setGlVersionMajor (const int majorVersion) {

    std::unique_lock<std::mutex> lock_glVersion(mutex_glVersion);

    if (!isOpen()) {
        m_glVersionMajor = majorVersion;
    } else {
        throw std::runtime_error("OpenGL version cannot be set while the window is open.");
    }

}

/**
 * Set the minor version of the OpenGL context.
 *
 * @param minorVersion new OpenGL minor version of the context
 */
void tw::Window::setGlVersionMinor (const int minorVersion) {

    std::unique_lock<std::mutex> lock_glVersion(mutex_glVersion);

    if (!isOpen()) {
        m_glVersionMinor = minorVersion;
    } else {
        throw std::runtime_error("OpenGL version cannot be set while the window is open.");
    }

}

/**
 * Set the version of the OpenGL context given a major version and a minor
 * version respectively.
 *
 * @param majorVersion new OpenGL major version of the context
 * @param minorVersion new OpenGL minor version of the context
 */
void tw::Window::setGlVersion (const int majorVersion, const int minorVersion) {

    std::unique_lock<std::mutex> lock_glVersion(mutex_glVersion);

    if (!isOpen()) {
        m_glVersionMajor = majorVersion;
        m_glVersionMinor = minorVersion;
    } else {
        throw std::runtime_error("OpenGL version cannot be set while the window is open.");
    }

}

/**
 * Inform GLFW of changes to the size of the window.
 */
void tw::Window::pushWindowSize () {

    if (m_context != NULL) {
        glfwSetWindowSize(m_context.get(), m_width, m_height);
    }

}

/**
 * Inform GLFW of changes to the title of the window.
 */
void tw::Window::pushWindowTitle () {

    if (m_context != NULL) {
        glfwSetWindowTitle(m_context.get(), m_title.c_str());
    }

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
void tw::Window::glLiveDebug (
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

std::unique_ptr<GLFWwindow, tw::Window::GLFWwindowDeleter> tw::Window::m_context; ///< GLFW window context

int tw::Window::m_width = 800; ///< width of the window
int tw::Window::m_height = 600; ///< height of the window
std::mutex tw::Window::mutex_size; ///< mutex for window height and width values

std::string tw::Window::m_title = ""; ///< window title
std::mutex tw::Window::mutex_title; ///< mutex for the window title

int tw::Window::m_glVersionMajor = 2; ///< major version of OpenGL context
int tw::Window::m_glVersionMinor = 1; ///< minor version of OpenGL context
std::mutex tw::Window::mutex_glVersion; ///< mutex for the OpenGL version

tw::Color tw::Window::m_lastClearColor {0.f, 0.f, 0.f, 1.f}; ///< last color used to clear the window
const tw::Color tw::Window::m_defaultClearColor {0.f, 0.f, 0.f, 1.f}; ///< default color for clearing the window
