#include "../include/LogObserver.hpp"

/**
 * @class tw::LogObserver
 *
 * Abstract class representing a log observer, to be stored in the static
 * tw::Log class. This class is meant to be extended by classes implementing the
 * specific logic to which you want log messages to be passed. The engine has
 * built in subclasses for sending to console, file, and arbitrary functions:
 * tw::ConsoleLogObserver, tw::FileLogObserver, and tw::FunctionLogObserver
 * respectively.
 */

/**
 * Constructor taking in a bitmask of allowed message log levels. Only the
 * specified log levels will be received, but all contexts will be received.
 *
 * @param allowedLevelFlags allowed log levels
 */
tw::LogObserver::LogObserver (unsigned int allowedLevelFlags)
: m_allowedLevelFlags(allowedLevelFlags) {}

/**
 * Constructor taking in a std::set of allowed contexts as std::strings. Only
 * the specified contexts will be received, but all log levels will be received.
 *
 * @param allowedContexts allowed contexts
 */
tw::LogObserver::LogObserver (const std::set<std::string>& allowedContexts)
: m_allowedContexts(allowedContexts), m_allContextsAllowed(false) {}

/**
 * Constructor taking in a variadic set of allowed contexts as std::strings.
 * Only the specified contexts will be received, but all log levels will be
 * received.
 *
 * @param allowedContexts allowed contexts
 */
tw::LogObserver::LogObserver (const std::string& allowedContexts...)
: m_allContextsAllowed(false) {

    m_allowedContexts.insert(allowedContexts);

}

/**
 * Constructor taking in a bitmask of allowed message log levels and a std::set
 * of allowed contexts as std::strings. Only the specified log levels and
 * contexts will be received.
 *
 * @param allowedLevelFlags allowed log levels
 * @param allowedContexts   allowed contexts
 */
tw::LogObserver::LogObserver (unsigned int allowedLevelFlags, const std::set<std::string>& allowedContexts)
: m_allowedLevelFlags(allowedLevelFlags), m_allowedContexts(allowedContexts), m_allContextsAllowed(false) {}

/**
 * Constructor taking in a bitmask of allowed message log levels and a variadic
 * set of allowed contexts as std::strings. Only the specified log levels and
 * contexts will be received.
 *
 * @param allowedLevelFlags allowed log levels
 * @param allowedContexts   allowed contexts
 */
tw::LogObserver::LogObserver (unsigned int allowedLevelFlags, const std::string& allowedContexts...)
: m_allowedLevelFlags(allowedLevelFlags), m_allContextsAllowed(false) {

    m_allowedContexts.insert(allowedContexts);

}

/**
 * Send a message to the log observer, checking if the log level and context is
 * allowed before forwarding the message to tw::LogObserver::notifyCallback.
 *
 * @param logLevel message log level
 * @param context  message context
 * @param message  message text
 */
void tw::LogObserver::notify (tw::LogLevel logLevel, const std::string& context, const std::string& message) {

    switch (logLevel) {

        case tw::LogLevel::UNDEFINED:
            if (!undefinedAllowed()) {
                return;
            }
            break;

        case tw::LogLevel::VERBOSE:
            if (!verboseAllowed()) {
                return;
            }
            break;

        case tw::LogLevel::NOTICE:
            if (!noticeAllowed()) {
                return;
            }
            break;

        case tw::LogLevel::WARNING:
            if (!warningAllowed()) {
                return;
            }
            break;

        case tw::LogLevel::ERROR:
            if (!errorAllowed()) {
                return;
            }
            break;

        default:
            return;

    }

    if (m_allContextsAllowed || contextAllowed(context)) {

        notifyCallback(logLevel, context, message);

    }

}

/**
 * Check if the undefined log level will be received.
 *
 * @return true if undefined log level is allowed, false if not
 */
bool tw::LogObserver::undefinedAllowed () const {

    return m_allowedLevelFlags & ALLOW_UNDEFINED;

}

/**
 * Allow reception of messages with undefined log level.
 */
void tw::LogObserver::allowUndefined () {

    m_allowedLevelFlags |= ALLOW_UNDEFINED;

}

/**
 * Disallow reception of messages with undefined log level.
 */
void tw::LogObserver::blockUndefined () {

    m_allowedLevelFlags &= ~ALLOW_UNDEFINED;

}

/**
 * Check if the verbose log level will be received.
 *
 * @return true if verbose log level is allowed, false if not
 */
bool tw::LogObserver::verboseAllowed () const {

    return m_allowedLevelFlags & ALLOW_VERBOSE;

}

/**
 * Allow reception of messages with verbose log level.
 */
void tw::LogObserver::allowVerbose () {

    m_allowedLevelFlags |= ALLOW_VERBOSE;

}

/**
 * Disallow reception of messages with verbose log level.
 */
void tw::LogObserver::blockVerbose () {

    m_allowedLevelFlags &= ~ALLOW_VERBOSE;

}

/**
 * Check if the notice log level will be received.
 *
 * @return true if notice log level is allowed, false if not
 */
bool tw::LogObserver::noticeAllowed () const {

    return m_allowedLevelFlags & ALLOW_NOTICE;

}

/**
 * Allow reception of messages with notice log level.
 */
void tw::LogObserver::allowNotice () {

    m_allowedLevelFlags |= ALLOW_NOTICE;

}

/**
 * Disallow reception of messages with notice log level.
 */
void tw::LogObserver::blockNotice () {

    m_allowedLevelFlags &= ~ALLOW_NOTICE;

}

/**
 * Check if the warning log level will be received.
 *
 * @return true if warning log level is allowed, false if not
 */
bool tw::LogObserver::warningAllowed () const {

    return m_allowedLevelFlags & ALLOW_WARNING;

}

/**
 * Allow reception of messages with warning log level.
 */
void tw::LogObserver::allowWarning () {

    m_allowedLevelFlags |= ALLOW_WARNING;

}

/**
 * Disallow reception of messages with warning log level.
 */
void tw::LogObserver::blockWarning () {

    m_allowedLevelFlags &= ~ALLOW_WARNING;

}

/**
 * Check if the error log level will be received.
 *
 * @return true if error log level is allowed, false if not
 */
bool tw::LogObserver::errorAllowed () const {

    return m_allowedLevelFlags & ALLOW_ERROR;

}

/**
 * Allow reception of messages with error log level.
 */
void tw::LogObserver::allowError () {

    m_allowedLevelFlags |= ALLOW_ERROR;

}

/**
 * Disallow reception of messages with error log level.
 */
void tw::LogObserver::blockError () {

    m_allowedLevelFlags &= ~ALLOW_ERROR;

}

/**
 * Check if the given context will be received.
 *
 * @param context context to check
 * @return true if the given context is allowed, false if not
 */
bool tw::LogObserver::contextAllowed (const std::string& context) const {

    return m_allowedContexts.find(context) != m_allowedContexts.end();

}

/**
 * Allow reception of messages with the given context(s).
 *
 * @param contexts contexts to allow
 */
void tw::LogObserver::allowContext(const std::string& contexts...) {

    m_allowedContexts.insert(contexts);

}

/**
 * Disallow reception of messages with the given context(s).
 *
 * @param contexts contexts to block
 */
void tw::LogObserver::blockContext(const std::string& contexts...) {

    m_allowedContexts.erase(contexts);

}

/**
 * Check if any context will be allowed (filtering contexts disabled).
 *
 * @return true if all contexts are accepted, false if they are filtered
 */
bool tw::LogObserver::allContextAllowed () const {

    return m_allContextsAllowed;

}

/**
 * Allow all contexts (disable context filtering).
 */
void tw::LogObserver::allowAllContext () {

    m_allContextsAllowed = true;

}

/**
 * Disallow all contexts not specifically allowed (enable context filtering).
 */
void tw::LogObserver::restrictContext () {

    m_allContextsAllowed = false;

}
