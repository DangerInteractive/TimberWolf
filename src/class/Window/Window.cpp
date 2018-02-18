#include "Window.hpp"

void Window::init () {

    Log::bindCallbacks();

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    Log::verbose("GLFW initialized.");

}

void Window::deinit () {

    glfwTerminate();

    Log::verbose("GLFW terminated.");

}

GLFWwindow* Window::getContext () {

    return m_context;

}

void Window::makeContextCurrent () {

    if (m_context != NULL) {
        glfwMakeContextCurrent(m_context);
        Log::verbose("Set GLFW window as current context.");
    } else {
        throw std::runtime_error("Cannot set NULL context current.");
    }

}

bool Window::isOpen () {

    return m_context != nullptr;

}

void Window::open () {

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_glVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_glVersionMinor);

    m_context = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);

    if (!m_context) {
        glfwTerminate();
        Log::error("Failed to get a window or OpenGL context.");
    }

    makeContextCurrent();

    glfwSwapInterval(1);

    GLenum glewStatus = glewInit();

    if (glewStatus != GLEW_OK) {
        Log::glewError(glewStatus);
    }

    Log::verbose("GLEW initialized.");

}

void Window::close () {

    if (isOpen()) {
        glfwSetWindowShouldClose(m_context, 1);
    }

}

void Window::destroy () {

    if (isOpen()) {
        glfwDestroyWindow(m_context); // equivalent to deleting
        m_context = nullptr;
    }

}

int Window::getWidth () {

    return m_width;

}

int Window::getHeight () {

    return m_height;

}

void Window::setWidth (const int width) {

    std::unique_lock<std::mutex> lock_size(mutex_size);

    m_width = width;
    pushWindowSize();

}

void Window::setHeight (const int height) {

    std::unique_lock<std::mutex> lock_size(mutex_size);

    m_height = height;
    pushWindowSize();

}

void Window::setSize (const int width, const int height) {

    std::unique_lock<std::mutex> lock_size(mutex_size);

    m_width = width;
    m_height = height;
    pushWindowSize();

}

std::string Window::getTitle () {

    return m_title;

}

void Window::setTitle (const std::string title) {

    std::unique_lock<std::mutex> lock_title(mutex_title);

    m_title = title;
    pushWindowTitle();

}

int Window::getGlVersionMajor () {

    return m_glVersionMajor;

}

int Window::getGlVersionMinor () {

    return m_glVersionMinor;

}

std::string Window::getGlVersion () {

    std::ostringstream oss;
    oss << m_glVersionMajor << '.' << m_glVersionMinor;
    return oss.str();

}

void Window::setGlVersionMajor (const int majorVersion) {

    std::unique_lock<std::mutex> lock_glVersion(mutex_glVersion);

    if (!isOpen()) {
        m_glVersionMajor = majorVersion;
    } else {
        throw std::runtime_error("OpenGL version cannot be set while the window is open.");
    }

}

void Window::setGlVersionMinor (const int minorVersion) {

    std::unique_lock<std::mutex> lock_glVersion(mutex_glVersion);

    if (!isOpen()) {
        m_glVersionMinor = minorVersion;
    } else {
        throw std::runtime_error("OpenGL version cannot be set while the window is open.");
    }

}

void Window::setGlVersion (const int majorVersion, const int minorVersion) {

    std::unique_lock<std::mutex> lock_glVersion(mutex_glVersion);

    if (!isOpen()) {
        m_glVersionMajor = majorVersion;
        m_glVersionMinor = minorVersion;
    } else {
        throw std::runtime_error("OpenGL version cannot be set while the window is open.");
    }

}

void Window::pushWindowSize () {

    if (m_context != NULL) {
        glfwSetWindowSize(m_context, m_width, m_height);
    }

}

void Window::pushWindowTitle () {

    if (m_context != NULL) {
        glfwSetWindowTitle(m_context, m_title.c_str());
    }

}

GLFWwindow* Window::m_context = nullptr;

int Window::m_width = 800;
int Window::m_height = 600;
std::mutex Window::mutex_size;

std::string Window::m_title = "";
std::mutex Window::mutex_title;

int Window::m_glVersionMajor = 2;
int Window::m_glVersionMinor = 1;
std::mutex Window::mutex_glVersion;
