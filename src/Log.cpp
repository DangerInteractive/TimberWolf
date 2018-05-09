#include "../include/Log.hpp"

/**
 * @class tw::Log
 *
 * Static class providing a global means of notifying all log observers
 * (polymorphic tw::LogObserver objects), and also storing and managing those
 * log observers.
 */

void tw::Log::bindUnhandledException () {

    std::set_terminate([](){
        tw::Log::error("system", "Unhandled exception.");
        std::abort();
    });

}

void tw::Log::registerObserver (std::unique_ptr<LogObserver>&& observer) {

    m_observers.push_back(std::move(observer));

}

void tw::Log::registerObserver (LogObserver* observer) {

    m_observers.emplace_back(observer);

}

std::mutex tw::Log::m_mutex;
std::vector<std::unique_ptr<tw::LogObserver>> tw::Log::m_observers {};
