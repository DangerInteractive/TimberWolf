#ifndef H_CLASS_LOG
#define H_CLASS_LOG

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <mutex>
#include <exception>
#include <cstdlib>
#include "../../enum/LogLevel/LogLevel.hpp"

class Log {

public:

    Log () = delete; // static only
    ~Log () = delete;

    Log (Log&&) = delete;
    Log& operator = (Log&&) = delete;

    Log (const Log&) = delete;
    Log& operator = (const Log&) = delete;

    static LogLevel getFilterLevel ();
    static void setFilterLevel (LogLevel);

    template<typename ...T>
    static void log (LogLevel messageType, T&&... message) {

        if (messageType == LogLevel::UNDEFINED || messageType >= m_filterLevel) {

            std::string out = Log::formatMessage(messageType, Log::concatMessage(std::forward<T>(message)...));

            if (messageType == LogLevel::ERROR) {
                std::unique_lock<std::mutex> lock_stderr(Log::mutex_stderr);
                std::cerr << out << std::endl;
            } else {
                std::unique_lock<std::mutex> lock_stdout(Log::mutex_stdout);
                std::cout << out << std::endl;
            }

        }

    }

    template<typename ...T>
    static void verbose (T&&... message) {
        Log::log(LogLevel::VERBOSE, std::forward<T>(message)...);
    }

    template<typename ...T>
    static void notice (T&&... message) {
        Log::log(LogLevel::NOTICE, std::forward<T>(message)...);
    }

    template<typename ...T>
    static void warning (T&&... message) {
        Log::log(LogLevel::WARNING, std::forward<T>(message)...);
    }

    template<typename ...T>
    static void error (T&&... message) {
        Log::log(LogLevel::ERROR, std::forward<T>(message)...);
    }

    static void bindUnhandledException ();
    static void unhandledException ();

private:

    template<typename ...T>
    static std::string concatMessage (T&&... message) {

        std::ostringstream oss;
        (oss << ... << std::forward<T>(message));
        return oss.str();

    }

    static std::string formatMessage (LogLevel, const std::string&);

    static LogLevel m_filterLevel;

    static std::mutex mutex_stdout;
    static std::mutex mutex_stderr;

};

#endif
