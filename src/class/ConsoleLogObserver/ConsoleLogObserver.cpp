#include "ConsoleLogObserver.hpp"

ConsoleLogObserver::ConsoleLogObserver (unsigned int allowedLevelFlags)
: LogObserver(allowedLevelFlags) {}

ConsoleLogObserver::ConsoleLogObserver (const std::set<std::string>& allowedContexts)
: LogObserver(allowedContexts) {}

ConsoleLogObserver::ConsoleLogObserver (const std::string& allowedContexts...)
: LogObserver(allowedContexts) {}

ConsoleLogObserver::ConsoleLogObserver (unsigned int allowedLevelFlags, const std::set<std::string>& allowedContexts)
: LogObserver(allowedLevelFlags, allowedContexts) {}

ConsoleLogObserver::ConsoleLogObserver (unsigned int allowedLevelFlags, const std::string& allowedContexts...)
: LogObserver(allowedLevelFlags, allowedContexts) {}

void ConsoleLogObserver::notifyCallback (LogLevel logLevel, const std::string& context, const std::string& message) {

    if (logLevel != LogLevel::ERROR) {
        Console::stdoutLine(formatMessage(logLevel, context, message));
    } else {
        Console::stderrLine(formatMessage(logLevel, context, message));
    }

}

std::string ConsoleLogObserver::formatMessage (LogLevel logLevel, const std::string& context, const std::string& message) const {

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
