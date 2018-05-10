#include "../include/FileLogObserver.hpp"

/**
 * @class tw::FileLogObserver
 *
 * Log observer that formats and routes messages to a log file.
 */

/**
 * Constructor taking in a file path as a std::string. All levels and contexts
 * will be received.
 *
 * @param filename file path
 */
tw::FileLogObserver::FileLogObserver (const std::string& filename)
: LogObserver(), m_file(filename, File::ENABLE_WRITE | File::ENABLE_APPEND) {}

/**
 * Constructor taking in a file path as a std::string and file opening flags.
 * Only the given levels will be received. All contexts will be received.
 *
 * @param filename          file path
 * @param allowedLevelFlags allowed log levels
 */
tw::FileLogObserver::FileLogObserver (const std::string& filename, unsigned int allowedLevelFlags)
: LogObserver(allowedLevelFlags), m_file(filename, File::ENABLE_WRITE | File::ENABLE_APPEND) {}

/**
 * Constructor taking in a file path as a std::string and a std::set of contexts
 * as std::strings. All log levels will be received. Only the provided contexts
 * will be received.
 *
 * @param filename        file path
 * @param allowedContexts set of allowed contexts
 */
tw::FileLogObserver::FileLogObserver (const std::string& filename, const std::set<std::string>& allowedContexts)
: LogObserver(allowedContexts), m_file(filename, File::ENABLE_WRITE | File::ENABLE_APPEND) {}

/**
 * Constructor taking in a file path as a std::string and a variadic set of
 * allowed contexts. All log levels will be received. Only the provided contexts
 * will be received.
 *
 * @param filename        file path
 * @param allowedContexts allowed contexts
 */
tw::FileLogObserver::FileLogObserver (const std::string& filename, const std::string& allowedContexts...)
: LogObserver(allowedContexts), m_file(filename, File::ENABLE_WRITE | File::ENABLE_APPEND) {}

/**
 * Constructor taking in a file path as a std::string, allowed log levels, and
 * a std::set of allowed contexts as std::strings. Only the provided levels and
 * contexts will be received.
 *
 * @param filename          file path
 * @param allowedLevelFlags allowed log levels
 * @param allowedContexts   allowed contexts
 */
tw::FileLogObserver::FileLogObserver (const std::string& filename, unsigned int allowedLevelFlags, const std::set<std::string>& allowedContexts)
: LogObserver(allowedLevelFlags, allowedContexts), m_file(filename, File::ENABLE_WRITE | File::ENABLE_APPEND) {}

/**
 * Constructor taking in a file path as a std::string, allowed log levels, and
 * a variadic set of allowed contexts. Only the provided levels and contexts
 * will be received.
 *
 * @param filename          file path
 * @param allowedLevelFlags allowed log levels
 * @param allowedContexts   allowed contexts
 */
tw::FileLogObserver::FileLogObserver (const std::string& filename, unsigned int allowedLevelFlags, const std::string& allowedContexts...)
: LogObserver(allowedLevelFlags, allowedContexts), m_file(filename, File::ENABLE_WRITE | File::ENABLE_APPEND) {}

/**
 * Get the path of the log file as a std::string.
 *
 * @return file path
 */
std::string tw::FileLogObserver::getFilePath () const {

    return m_file.getPath();

}

/**
 * Set the path of the log file to a provided std::string.
 *
 * @param path file path
 */
bool tw::FileLogObserver::setFilePath (const std::string& path) {

    if (!m_file.close()) {
        return false;
    }

    return m_file.setPath(path);

}

/**
 * Notify the file log observer of a message to be logged. This should only be
 * called by tw::LogObserver::notify().
 *
 * @param logLevel message log level
 * @param context  message context
 * @param message  message text
 */
void tw::FileLogObserver::notifyCallback (LogLevel logLevel, const std::string& context, const std::string& message) {

    if (!m_file.isOpen()) {
        if (!m_file.open()) {
            return;
        }
    }

    m_file.writeLine(formatMessage(logLevel, context, message));

}

/**
 * Format a message to be written to the log file.
 *
 * @param logLevel message log level
 * @param context  message context
 * @param message  message text
 * @return formatted message
 */
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
