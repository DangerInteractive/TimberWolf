#include "FunctionLogObserver.hpp"

void FunctionLogObserver::notifyCallback (LogLevel logLevel, const std::string& context, const std::string& message) {

    std::unique_lock<std::mutex> lock(m_mutex);

    for (unsigned int i = 0; i < m_callbacks.size(); ++i) {

        m_callbacks[i](logLevel, context, message);

    }

}

const std::vector<FunctionLogObserver::Callback>& FunctionLogObserver::getCallbacks () const {

    return m_callbacks;

}

void FunctionLogObserver::setCallbacks (const std::vector<Callback>& callbacks) {

    m_callbacks = callbacks;

}

void FunctionLogObserver::addCallback (const FunctionLogObserver::Callback& callback) {

    m_callbacks.push_back(callback);

}

void FunctionLogObserver::clearCallbacks () {

    m_callbacks.clear();

}
