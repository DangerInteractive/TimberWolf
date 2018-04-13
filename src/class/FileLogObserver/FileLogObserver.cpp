#include "FileLogObserver.hpp"

tw::FileLogObserver::FileLogObserver (const std::string& filename)
: LogObserver(), m_file(filename, File::ENABLE_WRITE | File::ENABLE_APPEND) {}

tw::FileLogObserver::FileLogObserver (const std::string& filename, unsigned int allowedLevelFlags)
: LogObserver(allowedLevelFlags), m_file(filename, File::ENABLE_WRITE | File::ENABLE_APPEND) {

    m_file.open();

}

tw::FileLogObserver::FileLogObserver (const std::string& filename, const std::set<std::string>& allowedContexts)
: LogObserver(allowedContexts), m_file(filename, File::ENABLE_WRITE | File::ENABLE_APPEND) {

    m_file.open();

}

tw::FileLogObserver::FileLogObserver (const std::string& filename, const std::string& allowedContexts...)
: LogObserver(allowedContexts), m_file(filename, File::ENABLE_WRITE | File::ENABLE_APPEND) {

    m_file.open();

}

tw::FileLogObserver::FileLogObserver (const std::string& filename, unsigned int allowedLevelFlags, const std::set<std::string>& allowedContexts)
: LogObserver(allowedLevelFlags, allowedContexts), m_file(filename, File::ENABLE_WRITE | File::ENABLE_APPEND) {

    m_file.open();

}

tw::FileLogObserver::FileLogObserver (const std::string& filename, unsigned int allowedLevelFlags, const std::string& allowedContexts...)
: LogObserver(allowedLevelFlags, allowedContexts), m_file(filename, File::ENABLE_WRITE | File::ENABLE_APPEND) {

    m_file.open();

}

std::string tw::FileLogObserver::getFilePath () const {

    return m_file.getPath();

}

bool tw::FileLogObserver::setFilePath (const std::string& path) {

    return m_file.setPath(path);

}

void tw::FileLogObserver::notifyCallback (LogLevel logLevel, const std::string& context, const std::string& message) {

    if (!m_file.isOpen()) {
        if (!m_file.open()) {
            return;
        }
    }

    m_file.writeLine(formatMessage(logLevel, context, message));

}

std::string tw::FileLogObserver::formatMessage (LogLevel logLevel, const std::string& context, const std::string& message) {

    auto time = std::time(nullptr);
    auto localtime = *std::localtime(&time);

    std::ostringstream oss;
    oss << std::put_time(&localtime, "%Y-%m-%d %H:%M:%S");
    oss << ' ';

    switch (logLevel) {

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

    oss << context << " : " << message;

    return oss.str();

}
