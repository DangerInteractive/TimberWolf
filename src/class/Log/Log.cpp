#include "Log.hpp"

LogLevel Log::getFilterLevel () {

    return m_filterLevel;

}

void Log::setFilterLevel (const LogLevel filterLevel) {

    m_filterLevel = filterLevel;

}

void Log::bindCallbacks () {

    glfwSetErrorCallback(glfwError);
    std::set_terminate(unhandledException);

}

void Log::unhandledException () {

    Log::error("Unhandled exception.");
    std::abort();

}

void Log::glfwError (int error, const char* description) {

    std::ostringstream oss;
    oss << std::showbase
        << std::internal
        << std::setfill('0');
    oss << "GLFW Error: "
        << std::dec << error << ' '
        << std::hex << std::setw(10) << error << ": " << std::dec
        << description;

    Log::error(oss.str());

}

void Log::glewError (GLenum glewStatus) {

    std::ostringstream oss;
    oss << "GLEW Error: "
        << glewGetErrorString(glewStatus);

    Log::error(oss.str());

}

std::string Log::formatMessage (LogLevel messageType, const std::string& message) {

    auto time = std::time(nullptr);
    auto localtime = *std::localtime(&time);

    std::ostringstream oss;
    oss << std::put_time(&localtime, "%Y-%m-%d %H:%M:%S");
    oss << ' ';

    switch (messageType) {

        case LogLevel::VERBOSE:
            oss << ". VERBOSE : ";
            break;

        case LogLevel::NOTICE:
            oss << "_ NOTICE  : ";
            break;

        case LogLevel::WARNING:
            oss << "! WARNING : ";
            break;

        case LogLevel::ERROR:
            oss << "# ERROR   : ";
            break;

        default:
            oss << "  UNKNOWN : ";
            break;

    }

    oss << message;

    return oss.str();

}

LogLevel Log::m_filterLevel = LogLevel::VERBOSE;

std::mutex Log::mutex_stdout;
std::mutex Log::mutex_stderr;
