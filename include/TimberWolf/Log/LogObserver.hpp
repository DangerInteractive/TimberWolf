#ifndef H_TW_LOGOBSERVER
#define H_TW_LOGOBSERVER

/**
 * @file
 *
 * Header file for the tw::LogObserver class.
 */

#include <string>
#include <set>
#include "LogLevel.hpp"
namespace tw{ class Log; }

namespace tw {
class LogObserver {

// WARNING: Never call Log::* functions from inside subclasses of this.
// It will cause infinite recursion and you will be sad.

public:

    static inline constexpr unsigned int ALLOW_UNDEFINED = 0b00001;
    static inline constexpr unsigned int ALLOW_VERBOSE =   0b00010;
    static inline constexpr unsigned int ALLOW_NOTICE =    0b00100;
    static inline constexpr unsigned int ALLOW_WARNING =   0b01000;
    static inline constexpr unsigned int ALLOW_ERROR =     0b10000;

    LogObserver () = default;
    explicit LogObserver (unsigned int);
    explicit LogObserver (const std::set<std::string>&);
    explicit LogObserver (const std::string&...);
    LogObserver (unsigned int, const std::set<std::string>&);
    LogObserver (unsigned int, const std::string&...);
    virtual ~LogObserver () = default;

    LogObserver (LogObserver&&) = default;
    LogObserver& operator = (LogObserver&&) = default;

    LogObserver (const LogObserver&) = default;
    LogObserver& operator = (const LogObserver&) = default;

    void notify (LogLevel, const std::string&, const std::string&);

    bool undefinedAllowed () const;
    void allowUndefined ();
    void blockUndefined ();
    bool verboseAllowed () const;
    void allowVerbose ();
    void blockVerbose ();
    bool noticeAllowed () const;
    void allowNotice ();
    void blockNotice ();
    bool warningAllowed () const;
    void allowWarning ();
    void blockWarning ();
    bool errorAllowed () const;
    void allowError ();
    void blockError ();

    bool contextAllowed (const std::string&) const;
    void allowContext (const std::string&...);
    void blockContext (const std::string&...);
    bool allContextAllowed () const;
    void allowAllContext ();
    void restrictContext ();

protected:

    virtual void notifyCallback (LogLevel, const std::string&, const std::string&) = 0;

    unsigned int m_allowedLevelFlags {
        ALLOW_UNDEFINED |
        ALLOW_VERBOSE |
        ALLOW_NOTICE |
        ALLOW_WARNING |
        ALLOW_ERROR
    };

    std::set<std::string> m_allowedContexts;
    bool m_allContextsAllowed {true};

};
}

#endif
