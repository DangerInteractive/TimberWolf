#ifndef H_CLASS_LOG
#define H_CLASS_LOG

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <ctime>
#include <mutex>
#include <exception>
#include <cstdlib>
#include <atomic>
#include "../../enum/LogLevel/LogLevel.hpp"

class Log {

public:

    Log () = delete; // static only
    ~Log () = delete;

    Log (Log&&) = delete;
    Log& operator = (Log&&) = delete;

    Log (const Log&) = delete;
    Log& operator = (const Log&) = delete;

    static bool cliOutputEnabled ();
    static void enableCliOutput ();
    static void disableCliOutput ();

    static LogLevel getCliFilterLevel ();
    static void setCliFilterLevel (LogLevel);

    static bool fileOpen ();
    static bool openFile (const std::string&);
    static void closeFile ();

    static bool fileOutputEnabled ();
    static void enableFileOutput ();
    static void disableFileOutput ();

    static LogLevel getFileFilterLevel ();
    static void setFileFilterLevel (LogLevel);

    template<typename ...T>
    static void log (LogLevel messageType, T&&... message) {

        std::string out;

        if (
            (m_cliOutputEnabled || m_fileOutputEnabled) &&
            (
                messageType == LogLevel::UNDEFINED ||
                messageType >= m_cliFilterLevel ||
                messageType >= m_fileFilterLevel
            )
        ) {
            out = Log::formatMessage(messageType, Log::concatMessage(std::forward<T>(message)...));
        }

        if (m_cliOutputEnabled) {
            if (messageType == LogLevel::UNDEFINED || messageType >= m_cliFilterLevel) {

                if (messageType == LogLevel::ERROR) {
                    std::unique_lock<std::mutex> lock_stderr(Log::mutex_stderr);
                    std::cerr << out << std::endl;
                } else {
                    std::unique_lock<std::mutex> lock_stdout(Log::mutex_stdout);
                    std::cout << out << std::endl;
                }

            }
        }

        if (m_fileOutputEnabled && fileOpen()) {
            if (messageType == LogLevel::UNDEFINED || messageType >= m_fileFilterLevel) {

                std::unique_lock<std::mutex> lock_file(Log::mutex_file);
                m_file << out << std::endl;

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

    static std::atomic<bool> m_cliOutputEnabled;
    static std::atomic<bool> m_fileOutputEnabled;

    static std::atomic<LogLevel> m_cliFilterLevel;
    static std::atomic<LogLevel> m_fileFilterLevel;

    static std::ofstream m_file;

    static std::mutex mutex_stdout;
    static std::mutex mutex_stderr;
    static std::mutex mutex_file;

};

#endif
