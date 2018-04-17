#include "../include/LogObserver.hpp"

tw::LogObserver::LogObserver (unsigned int allowedLevelFlags)
: m_allowedLevelFlags(allowedLevelFlags) {}

tw::LogObserver::LogObserver (const std::set<std::string>& allowedContexts)
: m_allowedContexts(allowedContexts), m_allContextsAllowed(false) {}

tw::LogObserver::LogObserver (const std::string& allowedContexts...)
: m_allContextsAllowed(false) {

    m_allowedContexts.insert(allowedContexts);

}

tw::LogObserver::LogObserver (unsigned int allowedLevelFlags, const std::set<std::string>& allowedContexts)
: m_allowedLevelFlags(allowedLevelFlags), m_allowedContexts(allowedContexts), m_allContextsAllowed(false) {}

tw::LogObserver::LogObserver (unsigned int allowedLevelFlags, const std::string& allowedContexts...)
: m_allowedLevelFlags(allowedLevelFlags), m_allContextsAllowed(false) {

    m_allowedContexts.insert(allowedContexts);

}

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

bool tw::LogObserver::undefinedAllowed () const {

    return m_allowedLevelFlags & ALLOW_UNDEFINED;

}

void tw::LogObserver::allowUndefined () {

    m_allowedLevelFlags |= ALLOW_UNDEFINED;

}

void tw::LogObserver::blockUndefined () {

    m_allowedLevelFlags &= ~ALLOW_UNDEFINED;

}

bool tw::LogObserver::verboseAllowed () const {

    return m_allowedLevelFlags & ALLOW_VERBOSE;

}

void tw::LogObserver::allowVerbose () {

    m_allowedLevelFlags |= ALLOW_VERBOSE;

}

void tw::LogObserver::blockVerbose () {

    m_allowedLevelFlags &= ~ALLOW_VERBOSE;

}

bool tw::LogObserver::noticeAllowed () const {

    return m_allowedLevelFlags & ALLOW_NOTICE;

}

void tw::LogObserver::allowNotice () {

    m_allowedLevelFlags |= ALLOW_NOTICE;

}

void tw::LogObserver::blockNotice () {

    m_allowedLevelFlags &= ~ALLOW_NOTICE;

}

bool tw::LogObserver::warningAllowed () const {

    return m_allowedLevelFlags & ALLOW_WARNING;

}

void tw::LogObserver::allowWarning () {

    m_allowedLevelFlags |= ALLOW_WARNING;

}

void tw::LogObserver::blockWarning () {

    m_allowedLevelFlags &= ~ALLOW_WARNING;

}

bool tw::LogObserver::errorAllowed () const {

    return m_allowedLevelFlags & ALLOW_ERROR;

}

void tw::LogObserver::allowError () {

    m_allowedLevelFlags |= ALLOW_ERROR;

}

void tw::LogObserver::blockError () {

    m_allowedLevelFlags &= ~ALLOW_ERROR;

}

bool tw::LogObserver::contextAllowed (const std::string& contexts...) const {

    return m_allowedContexts.find(contexts) != m_allowedContexts.end();

}

void tw::LogObserver::allowContext(const std::string& contexts...) {

    m_allowedContexts.insert(contexts);

}

void tw::LogObserver::blockContext(const std::string& contexts...) {

    m_allowedContexts.erase(contexts);

}

bool tw::LogObserver::allContextAllowed () const {

    return m_allContextsAllowed;

}

void tw::LogObserver::allowAllContext () {

    m_allContextsAllowed = true;

}

void tw::LogObserver::restrictContext () {

    m_allContextsAllowed = false;

}
