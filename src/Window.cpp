#include "../include/Window.hpp"

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

void tw::Window::deinit () {

    glfwTerminate();

    Log::verbose("window", "GLFW terminated.");

}

GLFWwindow* tw::Window::getContext () {

    return m_context.get();

}

void tw::Window::makeContextCurrent () {

    if (m_context != NULL) {
        glfwMakeContextCurrent(m_context.get());
        Log::verbose("window", "Set GLFW window as current context.");
    } else {
        throw std::runtime_error("Cannot set NULL context current.");
    }

}

bool tw::Window::isOpen () {

    return m_context != nullptr;

}

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

void tw::Window::close () {

    if (isOpen()) {
        glfwSetWindowShouldClose(m_context.get(), 1);
    }

}

void tw::Window::destroy () {

    if (isOpen()) {
        m_context.reset();
    }

}

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

int tw::Window::getWidth () {

    return m_width;

}

int tw::Window::getHeight () {

    return m_height;

}

void tw::Window::setWidth (const int width) {

    std::unique_lock<std::mutex> lock_size(mutex_size);

    m_width = width;
    pushWindowSize();

}

void tw::Window::setHeight (const int height) {

    std::unique_lock<std::mutex> lock_size(mutex_size);

    m_height = height;
    pushWindowSize();

}

void tw::Window::setSize (const int width, const int height) {

    std::unique_lock<std::mutex> lock_size(mutex_size);

    m_width = width;
    m_height = height;
    pushWindowSize();

}

std::string tw::Window::getTitle () {

    return m_title;

}

void tw::Window::setTitle (const std::string& title) {

    std::unique_lock<std::mutex> lock_title(mutex_title);

    m_title = title;
    pushWindowTitle();

}

int tw::Window::getGlVersionMajor () {

    return m_glVersionMajor;

}

int tw::Window::getGlVersionMinor () {

    return m_glVersionMinor;

}

std::string tw::Window::getGlVersion () {

    std::ostringstream oss;
    oss << m_glVersionMajor << '.' << m_glVersionMinor;
    return oss.str();

}

void tw::Window::setGlVersionMajor (const int majorVersion) {

    std::unique_lock<std::mutex> lock_glVersion(mutex_glVersion);

    if (!isOpen()) {
        m_glVersionMajor = majorVersion;
    } else {
        throw std::runtime_error("OpenGL version cannot be set while the window is open.");
    }

}

void tw::Window::setGlVersionMinor (const int minorVersion) {

    std::unique_lock<std::mutex> lock_glVersion(mutex_glVersion);

    if (!isOpen()) {
        m_glVersionMinor = minorVersion;
    } else {
        throw std::runtime_error("OpenGL version cannot be set while the window is open.");
    }

}

void tw::Window::setGlVersion (const int majorVersion, const int minorVersion) {

    std::unique_lock<std::mutex> lock_glVersion(mutex_glVersion);

    if (!isOpen()) {
        m_glVersionMajor = majorVersion;
        m_glVersionMinor = minorVersion;
    } else {
        throw std::runtime_error("OpenGL version cannot be set while the window is open.");
    }

}

void tw::Window::pushWindowSize () {

    if (m_context != NULL) {
        glfwSetWindowSize(m_context.get(), m_width, m_height);
    }

}

void tw::Window::pushWindowTitle () {

    if (m_context != NULL) {
        glfwSetWindowTitle(m_context.get(), m_title.c_str());
    }

}

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
    for (unsigned int i = 0; i < length; ++i) {
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

std::unique_ptr<GLFWwindow, tw::Window::GLFWwindowDeleter> tw::Window::m_context;

int tw::Window::m_width = 800;
int tw::Window::m_height = 600;
std::mutex tw::Window::mutex_size;

std::string tw::Window::m_title = "";
std::mutex tw::Window::mutex_title;

int tw::Window::m_glVersionMajor = 2;
int tw::Window::m_glVersionMinor = 1;
std::mutex tw::Window::mutex_glVersion;

tw::Color tw::Window::m_lastClearColor {0.f, 0.f, 0.f, 1.f};
const tw::Color tw::Window::m_defaultClearColor {0.f, 0.f, 0.f, 1.f};
