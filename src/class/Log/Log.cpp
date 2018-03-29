#include "Log.hpp"

bool Log::cliOutputEnabled () {

    return m_cliOutputEnabled;

}

void Log::enableCliOutput () {

    m_cliOutputEnabled = true;

}

void Log::disableCliOutput () {

    m_cliOutputEnabled = false;

}

LogLevel Log::getCliFilterLevel () {

    return m_cliFilterLevel;

}

void Log::setCliFilterLevel (LogLevel filterLevel) {

    m_cliFilterLevel = filterLevel;

}

bool Log::fileOpen () {

    return m_file.is_open();

}

bool Log::openFile (const std::string& filename) {

    if (fileOpen()) {
        closeFile();
    }

    m_file.open(filename, std::ios::out | std::ios::app);

    return fileOpen();

}

void Log::closeFile () {

    if (fileOpen()) {
        m_file.close();
    }

}

bool Log::fileOutputEnabled () {

    return m_fileOutputEnabled;

}

void Log::enableFileOutput () {

    m_fileOutputEnabled = true;

}

void Log::disableFileOutput () {

    m_fileOutputEnabled = false;

}

LogLevel Log::getFileFilterLevel () {

    return m_fileFilterLevel;

}

void Log::setFileFilterLevel (LogLevel filterLevel) {

    m_fileFilterLevel = filterLevel;

}

void Log::bindUnhandledException () {

    std::set_terminate(unhandledException);

}

void Log::unhandledException () {

    Log::error("Unhandled exception.");
    std::abort();

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

std::atomic<bool> Log::m_cliOutputEnabled {true};
std::atomic<bool> Log::m_fileOutputEnabled {false};

std::atomic<LogLevel> Log::m_cliFilterLevel {LogLevel::VERBOSE};
std::atomic<LogLevel> Log::m_fileFilterLevel {LogLevel::VERBOSE};

std::ofstream Log::m_file;

std::mutex Log::mutex_stdout;
std::mutex Log::mutex_stderr;
std::mutex Log::mutex_file;
