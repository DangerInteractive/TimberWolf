#include "FunctionLogObserver.hpp"

FunctionLogObserver::FunctionLogObserver (const std::vector<FunctionLogObserver::Callback>& callbacks)
: LogObserver() {

    setCallbacks(callbacks);

}

FunctionLogObserver::FunctionLogObserver (const Callback& callbacks...)
: LogObserver() {

    addCallback(callbacks);

}

FunctionLogObserver::FunctionLogObserver (const std::vector<FunctionLogObserver::Callback>& callbacks, unsigned int allowedLevelFlags)
: LogObserver(allowedLevelFlags) {

    setCallbacks(callbacks);

}

FunctionLogObserver::FunctionLogObserver (const FunctionLogObserver::Callback& callback, unsigned int allowedLevelFlags)
: LogObserver(allowedLevelFlags) {

    addCallback(callback);

}

FunctionLogObserver::FunctionLogObserver (const std::vector<FunctionLogObserver::Callback>& callbacks, const std::set<std::string>& allowedContexts)
: LogObserver(allowedContexts) {

    setCallbacks(callbacks);

}

FunctionLogObserver::FunctionLogObserver (const FunctionLogObserver::Callback& callback, const std::set<std::string>& allowedContexts)
: LogObserver(allowedContexts) {

    addCallback(callback);

}

FunctionLogObserver::FunctionLogObserver (const std::vector<FunctionLogObserver::Callback>& callbacks, const std::string& allowedContexts...)
: LogObserver(allowedContexts) {

    setCallbacks(callbacks);

}

FunctionLogObserver::FunctionLogObserver (const FunctionLogObserver::Callback& callback, const std::string& allowedContexts...)
: LogObserver(allowedContexts) {

    addCallback(callback);

}

FunctionLogObserver::FunctionLogObserver (const std::vector<FunctionLogObserver::Callback>& callbacks, unsigned int allowedLevelFlags, const std::set<std::string>& allowedContexts)
: LogObserver(allowedLevelFlags, allowedContexts) {

    setCallbacks(callbacks);

}

FunctionLogObserver::FunctionLogObserver (const FunctionLogObserver::Callback& callback, unsigned int allowedLevelFlags, const std::set<std::string>& allowedContexts)
: LogObserver(allowedLevelFlags, allowedContexts) {

    addCallback(callback);

}

FunctionLogObserver::FunctionLogObserver (const std::vector<FunctionLogObserver::Callback>& callbacks, unsigned int allowedLevelFlags, const std::string& allowedContexts...)
: LogObserver(allowedLevelFlags, allowedContexts) {

    setCallbacks(callbacks);

}

FunctionLogObserver::FunctionLogObserver (const FunctionLogObserver::Callback& callback, unsigned int allowedLevelFlags, const std::string& allowedContexts...)
: LogObserver(allowedLevelFlags, allowedContexts) {

    addCallback(callback);

}

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

void FunctionLogObserver::addCallback (const FunctionLogObserver::Callback& callback...) {

    m_callbacks.push_back(callback);

}

void FunctionLogObserver::clearCallbacks () {

    m_callbacks.clear();

}
