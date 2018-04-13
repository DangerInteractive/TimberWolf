#include "ConsoleLogObserver.hpp"

void tw::ConsoleLogObserver::notifyCallback (LogLevel logLevel, const std::string& context, const std::string& message) {

    if (logLevel != tw::LogLevel::ERROR) {
        Console::stdoutLine(formatMessage(logLevel, context, message));
    } else {
        Console::stderrLine(formatMessage(logLevel, context, message));
    }

}

std::string tw::ConsoleLogObserver::formatMessage (LogLevel logLevel, const std::string& context, const std::string& message) const {

    auto time = std::time(nullptr);
    auto localtime = *std::localtime(&time);

    std::ostringstream oss;
    oss << std::put_time(&localtime, "%Y-%m-%d %H:%M:%S");
    oss << ' ';

    switch (logLevel) {

        case tw::LogLevel::VERBOSE:
            oss << ". VERBOSE : ";
            break;

        case tw::LogLevel::NOTICE:
            oss << "_ NOTICE  : ";
            break;

        case tw::LogLevel::WARNING:
            oss << "! WARNING : ";
            break;

        case tw::LogLevel::ERROR:
            oss << "# ERROR   : ";
            break;

        default:
            oss << "  UNKNOWN : ";
            break;

    }

    oss << context << " : " << message;

    return oss.str();

}
