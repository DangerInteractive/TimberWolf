#ifndef H_TW_LOG
#define H_TW_LOG

/**
 * @file
 *
 * Header file for the tw::Log class.
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <mutex>
#include <functional>
#include "LogObserver.hpp"
#include "LogLevel.hpp"

namespace tw {
class Log {

public:

    Log () = delete; // static only
    ~Log () = delete;

    Log (Log&&) = delete;
    Log& operator = (Log&&) = delete;

    Log (const Log&) = delete;
    Log& operator = (const Log&) = delete;

    template <typename ...T>
    static void log (LogLevel messageType, const std::string& context, T&&... message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        for (unsigned int i = 0; i < m_observers.size(); ++i) {

            m_observers[i]->notify(messageType, context, concatMessage(std::forward<T>(message)...));

        }

    }

    template <typename ...T>
    static void verbose (const std::string& context, T&&... message) {
        Log::log(LogLevel::VERBOSE, context, std::forward<T>(message)...);
    }

    template <typename ...T>
    static void notice (const std::string& context, T&&... message) {
        Log::log(LogLevel::NOTICE, context, std::forward<T>(message)...);
    }

    template <typename ...T>
    static void warning (const std::string& context, T&&... message) {
        Log::log(LogLevel::WARNING, context, std::forward<T>(message)...);
    }

    template <typename ...T>
    static void error (const std::string& context, T&&... message) {
        Log::log(LogLevel::ERROR, context, std::forward<T>(message)...);
    }

    static void bindUnhandledException ();

    template <typename T, typename ...Targ>
    static LogObserver* makeObserver (Targ&&... args) {

        auto observer = std::make_unique<T>(std::forward<Targ>(args)...);
        auto observerPtr = observer.get();

        m_observers.push_back(std::move(observer));

        return observerPtr;

    }
    static void registerObserver (std::unique_ptr<LogObserver>&&);
    static void registerObserver (LogObserver*);

private:

    template <typename ...T>
    static std::string concatMessage (T&&... message) {

        std::ostringstream oss;
        (oss << ... << std::forward<T>(message));
        return oss.str();

    }

    static std::mutex m_mutex;
    static std::vector<std::unique_ptr<LogObserver>> m_observers;

};
}

#endif
