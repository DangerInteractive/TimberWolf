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

    if (m_renderer != nullptr) {
        m_renderer->onWindowOpen();
    }

}

/**
 * Close the window. This should be done before calling tw::Window::destroy.
 */
void tw::Window::close () {

    if (isOpen()) {
        glfwSetWindowShouldClose(m_context.get(), 1);
    }

    if (m_renderer != nullptr) {
        m_renderer->onWindowClose();
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
 * Get a pointer to the window's renderer object. May be nullptr.
 *
 * @return pointer to renderer if set, nullptr if not
 */
tw::Renderer* tw::Window::getRenderer () {

    return m_renderer.get();

}

/**
 * Set the window's renderer object to a given pointer. Note that this will
 * create a std::unique_ptr from the pointer, and it may get deleted
 * automatically.
 *
 * @param renderer pointer to new renderer
 */
void tw::Window::setRenderer (Renderer* renderer) {

    m_renderer = std::unique_ptr<Renderer>(renderer);

    if (isOpen()) {
        if (m_renderer != nullptr) {
            m_renderer->onWindowOpen();
        }
    }

}

/**
 * @fn tw::Window::makeRenderer
 *
 * Create a new renderer object and attach it to the Window, and then return a
 * pointer to the newly created renderer.
 *
 * @tparam T    type of renderer to create
 * @tparam TArg variadic types of arguments passed to T constructor (automatically deduced)
 * @param  args variadic arguments to pass to T constructor
 * @return newly created renderer
 */

/**
 * Clear the color and depth buffers between draws, using the default clear
 * color.
 */
void tw::Window::clear () {

    if (isOpen()) {
        if (m_renderer != nullptr) {
            m_renderer->clear();
        }
    }

}

/**
 * Clear the color buffer between draws using the default clear color.
 */
void tw::Window::clearColor () {

    if (isOpen()) {
        if (m_renderer != nullptr) {
            m_renderer->clearColor();
        }
    }

}

/**
 * Clear the depth buffer between draws.
 */
void tw::Window::clearDepth () {

    if (isOpen()) {
        if (m_renderer != nullptr) {
            m_renderer->clearDepth();
        }
    }

}

/**
 * Set the color buffer clear color (persists to all folllowing draws).
 */
void tw::Window::setClearColor (const Color& color) {

    if (m_renderer != nullptr) {
        m_renderer->setClearColor(color);
    }

}

/**
 * Set the color buffer clear color (persists to all following draws).
 */
void tw::Window::setClearColor (float r, float g, float b, float a) {

    if (m_renderer != nullptr) {
        m_renderer->setClearColor(r, g, b, a);
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

    if (m_context != nullptr) {
        glfwSetWindowSize(m_context.get(), m_width, m_height);
    }

}

/**
 * Inform GLFW of changes to the title of the window.
 */
void tw::Window::pushWindowTitle () {

    if (m_context != nullptr) {
        glfwSetWindowTitle(m_context.get(), m_title.c_str());
    }

}

std::unique_ptr<GLFWwindow, tw::Window::GLFWwindowDeleter> tw::Window::m_context {nullptr}; ///< GLFW window context

std::unique_ptr<tw::Renderer> tw::Window::m_renderer {nullptr};

int tw::Window::m_width = 800; ///< width of the window
int tw::Window::m_height = 600; ///< height of the window
std::mutex tw::Window::mutex_size; ///< mutex for window height and width values

std::string tw::Window::m_title = ""; ///< window title
std::mutex tw::Window::mutex_title; ///< mutex for the window title

int tw::Window::m_glVersionMajor = 2; ///< major version of OpenGL context
int tw::Window::m_glVersionMinor = 1; ///< minor version of OpenGL context
std::mutex tw::Window::mutex_glVersion; ///< mutex for the OpenGL version
