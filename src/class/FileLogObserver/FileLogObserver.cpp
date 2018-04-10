#include "FileLogObserver.hpp"

FileLogObserver::FileLogObserver (unsigned int allowedLevelFlags)
: LogObserver(allowedLevelFlags) {

    m_file.open();

}

FileLogObserver::FileLogObserver (const std::set<std::string>& allowedContexts)
: LogObserver(allowedContexts) {

    m_file.open();

}

FileLogObserver::FileLogObserver (const std::string& allowedContexts...)
: LogObserver(allowedContexts) {

    m_file.open();

}

FileLogObserver::FileLogObserver (unsigned int allowedLevelFlags, const std::set<std::string>& allowedContexts)
: LogObserver(allowedLevelFlags, allowedContexts) {

    m_file.open();

}

FileLogObserver::FileLogObserver (unsigned int allowedLevelFlags, const std::string& allowedContexts...)
: LogObserver(allowedLevelFlags, allowedContexts) {

    m_file.open();

}

void FileLogObserver::notifyCallback (LogLevel logLevel, const std::string& context, const std::string& message) {

    m_file.writeLine(formatMessage(logLevel, context, message));

}

std::string FileLogObserver::formatMessage (LogLevel logLevel, const std::string& context, const std::string& message) {

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
