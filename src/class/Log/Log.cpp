#include "Log.hpp"

void Log::bindUnhandledException () {

    std::set_terminate([](){
        Log::error("system", "Unhandled exception.");
        std::abort();
    });

}

void Log::registerObserver (std::unique_ptr<LogObserver>&& observer) {

    m_observers.push_back(std::move(observer));

}

void Log::registerObserver (LogObserver* observer) {

    m_observers.emplace_back(observer);

}

std::mutex Log::m_mutex;
std::vector<std::unique_ptr<LogObserver>> Log::m_observers {};
