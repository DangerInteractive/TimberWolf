#ifndef H_CLASS_FUNCTIONLOGOBSERVER
#define H_CLASS_FUNCTIONLOGOBSERVER

#include <string>
#include <set>
#include <vector>
#include <functional>
#include <mutex>
#include "../LogObserver/LogObserver.hpp"

class FunctionLogObserver : public LogObserver {

public:

    typedef std::function<void(LogLevel, const std::string&, const std::string&)> Callback;

    FunctionLogObserver () = default;
    explicit FunctionLogObserver (unsigned int);
    explicit FunctionLogObserver (const std::set<std::string>&);
    explicit FunctionLogObserver (const std::string&...);
    FunctionLogObserver (unsigned int, const std::set<std::string>&);
    FunctionLogObserver (unsigned int, const std::string&...);
    virtual ~FunctionLogObserver () = default;

    FunctionLogObserver (FunctionLogObserver&&) = default;
    FunctionLogObserver& operator = (FunctionLogObserver&&) = default;

    FunctionLogObserver (const FunctionLogObserver&) = default;
    FunctionLogObserver& operator = (const FunctionLogObserver&) = default;

    const std::vector<Callback>& getCallbacks () const;
    void setCallbacks (const std::vector<Callback>&);
    void addCallback (const Callback&);
    void clearCallbacks ();

protected:

    virtual void notifyCallback (LogLevel, const std::string&, const std::string&);

    std::mutex m_mutex;
    std::vector<Callback> m_callbacks;

};

#endif
