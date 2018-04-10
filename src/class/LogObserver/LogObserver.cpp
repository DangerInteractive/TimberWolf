#include "LogObserver.hpp"

LogObserver::LogObserver (unsigned int allowedLevelFlags)
: m_allowedLevelFlags(allowedLevelFlags) {}

LogObserver::LogObserver (const std::set<std::string>& allowedContexts)
: m_allowedContexts(allowedContexts), m_allContextsAllowed(false) {}

LogObserver::LogObserver (const std::string& allowedContexts...)
: m_allContextsAllowed(false) {

    m_allowedContexts.insert(allowedContexts);

}

LogObserver::LogObserver (unsigned int allowedLevelFlags, const std::set<std::string>& allowedContexts)
: m_allowedLevelFlags(allowedLevelFlags), m_allowedContexts(allowedContexts), m_allContextsAllowed(false) {}

LogObserver::LogObserver (unsigned int allowedLevelFlags, const std::string& allowedContexts...)
: m_allowedLevelFlags(allowedLevelFlags), m_allContextsAllowed(false) {

    m_allowedContexts.insert(allowedContexts);

}

void LogObserver::notify (LogLevel logLevel, const std::string& context, const std::string& message) {

    switch (logLevel) {

        case LogLevel::UNDEFINED:
            if (!undefinedAllowed()) {
                return;
            }
            break;

        case LogLevel::VERBOSE:
            if (!verboseAllowed()) {
                return;
            }
            break;

        case LogLevel::NOTICE:
            if (!noticeAllowed()) {
                return;
            }
            break;

        case LogLevel::WARNING:
            if (!warningAllowed()) {
                return;
            }
            break;

        case LogLevel::ERROR:
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

bool LogObserver::undefinedAllowed () const {

    return m_allowedLevelFlags & ALLOW_UNDEFINED;

}

void LogObserver::allowUndefined () {

    m_allowedLevelFlags |= ALLOW_UNDEFINED;

}

void LogObserver::blockUndefined () {

    m_allowedLevelFlags &= ~ALLOW_UNDEFINED;

}

bool LogObserver::verboseAllowed () const {

    return m_allowedLevelFlags & ALLOW_VERBOSE;

}

void LogObserver::allowVerbose () {

    m_allowedLevelFlags |= ALLOW_VERBOSE;

}

void LogObserver::blockVerbose () {

    m_allowedLevelFlags &= ~ALLOW_VERBOSE;

}

bool LogObserver::noticeAllowed () const {

    return m_allowedLevelFlags & ALLOW_NOTICE;

}

void LogObserver::allowNotice () {

    m_allowedLevelFlags |= ALLOW_NOTICE;

}

void LogObserver::blockNotice () {

    m_allowedLevelFlags &= ~ALLOW_NOTICE;

}

bool LogObserver::warningAllowed () const {

    return m_allowedLevelFlags & ALLOW_WARNING;

}

void LogObserver::allowWarning () {

    m_allowedLevelFlags |= ALLOW_WARNING;

}

void LogObserver::blockWarning () {

    m_allowedLevelFlags &= ~ALLOW_WARNING;

}

bool LogObserver::errorAllowed () const {

    return m_allowedLevelFlags & ALLOW_ERROR;

}

void LogObserver::allowError () {

    m_allowedLevelFlags |= ALLOW_ERROR;

}

void LogObserver::blockError () {

    m_allowedLevelFlags &= ~ALLOW_ERROR;

}

bool LogObserver::contextAllowed (const std::string& contexts...) const {

    return m_allowedContexts.find(contexts) != m_allowedContexts.end();

}

void LogObserver::allowContext(const std::string& contexts...) {

    m_allowedContexts.insert(contexts);

}

void LogObserver::blockContext(const std::string& contexts...) {

    m_allowedContexts.erase(contexts);

}

bool LogObserver::allContextAllowed () const {

    return m_allContextsAllowed;

}

void LogObserver::allowAllContext () {

    m_allContextsAllowed = true;

}

void LogObserver::restrictContext () {

    m_allContextsAllowed = false;

}
