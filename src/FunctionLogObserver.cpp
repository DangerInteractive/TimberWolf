#include "../include/FunctionLogObserver.hpp"

/**
 * @class tw::FunctionLogObserver
 *
 * Log observer that stores a collection of callbacks and routes messages to
 * them.
 */

/**
 * Constructor taking in a std::vector of callbacks. All log levels and contexts
 * will be received.
 *
 * @param callbacks callbacks
 */
tw::FunctionLogObserver::FunctionLogObserver (const std::vector<Callback>& callbacks)
: LogObserver() {

    setCallbacks(callbacks);

}

/**
 * Constructor taking in a variadic set of callbacks. All log levels and
 * contexts will be received.
 *
 * @param callbacks callbacks
 */
tw::FunctionLogObserver::FunctionLogObserver (const Callback& callbacks...)
: LogObserver() {

    addCallback(callbacks);

}

/**
 * Constructor taking in a std::vector of callbacks and allowed log levels. Only
 * the provided log levels will be received. All contexts will be received.
 *
 * @param callbacks         callbacks
 * @param allowedLevelFlags allowed log levels
 */
tw::FunctionLogObserver::FunctionLogObserver (const std::vector<Callback>& callbacks, unsigned int allowedLevelFlags)
: LogObserver(allowedLevelFlags) {

    setCallbacks(callbacks);

}

/**
 * Constructor taking in a callback and allowed log levels. Only the provided
 * log levels will be received. All contexts will be received.
 *
 * @param callback          callback
 * @param allowedLevelFlags allowed log levels
 */
tw::FunctionLogObserver::FunctionLogObserver (const Callback& callback, unsigned int allowedLevelFlags)
: LogObserver(allowedLevelFlags) {

    addCallback(callback);

}

/**
 * Constructor taking in a std::vector of callbacks and a std::set of allowed
 * contexts. All log levels will be received. Only the provided contexts will be
 * received.
 *
 * @param callbacks       callbacks
 * @param allowedContexts allowed contexts
 */
tw::FunctionLogObserver::FunctionLogObserver (const std::vector<Callback>& callbacks, const std::set<std::string>& allowedContexts)
: LogObserver(allowedContexts) {

    setCallbacks(callbacks);

}

/**
 * Constructor taking in a callback and a std::set of allowed contexts. All log
 * levels will be received. Only the provided contexts will be received.
 * @param callback        callback
 * @param allowedContexts allowed contexts
 */
tw::FunctionLogObserver::FunctionLogObserver (const Callback& callback, const std::set<std::string>& allowedContexts)
: LogObserver(allowedContexts) {

    addCallback(callback);

}

/**
 * Constructor taking in a std::vector of callbacks and a variadic set of
 * allowed contexts. All log levels will be received. Only the provided contexts
 * will be received.
 *
 * @param callbacks       callbacks
 * @param allowedContexts allowed contexts
 */
tw::FunctionLogObserver::FunctionLogObserver (const std::vector<Callback>& callbacks, const std::string& allowedContexts...)
: LogObserver(allowedContexts) {

    setCallbacks(callbacks);

}

/**
 * Constructor taking in a callback and a variadic set of allowed contexts. All
 * log levels will be received. Only the provided contexts will be received.
 *
 * @param callback        callback
 * @param allowedContexts allowed contexts
 */
tw::FunctionLogObserver::FunctionLogObserver (const Callback& callback, const std::string& allowedContexts...)
: LogObserver(allowedContexts) {

    addCallback(callback);

}

/**
 * Constructor taking in a std::vector of callbacks, allowed log levels, and a
 * std::set of allowed contexts. Only the provided log levels and contexts will
 * be received.
 *
 * @param callbacks         callbacks
 * @param allowedLevelFlags allowed log levels
 * @param allowedContexts   allowed contexts
 */
tw::FunctionLogObserver::FunctionLogObserver (const std::vector<Callback>& callbacks, unsigned int allowedLevelFlags, const std::set<std::string>& allowedContexts)
: LogObserver(allowedLevelFlags, allowedContexts) {

    setCallbacks(callbacks);

}

/**
 * Constructor taking in a callback, allowed log levels, and a std::set of
 * allowed contexts. Only the provided log levels and contexts will be received.
 *
 * @param callback          callback
 * @param allowedLevelFlags allowed log levels
 * @param allowedContexts   allowed contexts
 */
tw::FunctionLogObserver::FunctionLogObserver (const Callback& callback, unsigned int allowedLevelFlags, const std::set<std::string>& allowedContexts)
: LogObserver(allowedLevelFlags, allowedContexts) {

    addCallback(callback);

}

/**
 * Constructor taking in a std::vector of callbacks, allowed log levels, and a
 * std::set of allowed contexts. Only the provided log levels and contexts will
 * be received.
 *
 * @param callbacks         callbacks
 * @param allowedLevelFlags allowed log levels
 * @param allowedContexts   allowed contexts
 */
tw::FunctionLogObserver::FunctionLogObserver (const std::vector<Callback>& callbacks, unsigned int allowedLevelFlags, const std::string& allowedContexts...)
: LogObserver(allowedLevelFlags, allowedContexts) {

    setCallbacks(callbacks);

}

/**
 * Constructor taking in a callback, allowed log levels, and a variadic set of
 * allowed contexts. Only the provided log levels and contexts will be received.
 *
 * @param callback          callback
 * @param allowedLevelFlags allowed log levels
 * @param [name]            allowed contexts
 */
tw::FunctionLogObserver::FunctionLogObserver (const Callback& callback, unsigned int allowedLevelFlags, const std::string& allowedContexts...)
: LogObserver(allowedLevelFlags, allowedContexts) {

    addCallback(callback);

}

/**
 * Notify the function log observer of a message to be sent to its callbacks.
 * This should only be called by tw::LogObserver::notify().
 *
 * @param logLevel message log level
 * @param context  message context
 * @param message  message text
 */
void tw::FunctionLogObserver::notifyCallback (LogLevel logLevel, const std::string& context, const std::string& message) {

    std::unique_lock<std::mutex> lock(m_mutex);

    for (unsigned int i = 0; i < m_callbacks.size(); ++i) {

        m_callbacks[i](logLevel, context, message);

    }

}

/**
 * Get a std::vector of attached callbacks.
 *
 * @return attached callbacks
 */
const std::vector<tw::FunctionLogObserver::Callback>& tw::FunctionLogObserver::getCallbacks () const {

    return m_callbacks;

}

/**
 * Replace all attached callbacks with a given std::vector of callbacks.
 *
 * @param callbacks new callbacks
 */
void tw::FunctionLogObserver::setCallbacks (const std::vector<Callback>& callbacks) {

    m_callbacks = callbacks;

}

/**
 * Attach one or more callbacks.
 *
 * @param callback callbacks
 */
void tw::FunctionLogObserver::addCallback (const Callback& callback...) {

    m_callbacks.push_back(callback);

}

/**
 * Remove all attached callbacks.
 */
void tw::FunctionLogObserver::clearCallbacks () {

    m_callbacks.clear();

}
