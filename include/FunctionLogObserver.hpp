#ifndef H_TW_FUNCTIONLOGOBSERVER
#define H_TW_FUNCTIONLOGOBSERVER

#include <string>
#include <set>
#include <vector>
#include <functional>
#include <mutex>
#include "LogObserver.hpp"

namespace tw {
class FunctionLogObserver : public LogObserver {

public:

    typedef std::function<void(LogLevel, const std::string&, const std::string&)> Callback;

    FunctionLogObserver () = default;
    explicit FunctionLogObserver (const std::vector<Callback>&);
    explicit FunctionLogObserver (const Callback&...);
    FunctionLogObserver (const std::vector<Callback>&, unsigned int);
    FunctionLogObserver (const Callback&, unsigned int);
    FunctionLogObserver (const std::vector<Callback>&, const std::set<std::string>&);
    FunctionLogObserver (const Callback&, const std::set<std::string>&);
    FunctionLogObserver (const std::vector<Callback>&, const std::string&...);
    FunctionLogObserver (const Callback&, const std::string&...);
    FunctionLogObserver (const std::vector<Callback>&, unsigned int, const std::set<std::string>&);
    FunctionLogObserver (const Callback&, unsigned int, const std::set<std::string>&);
    FunctionLogObserver (const std::vector<Callback>&, unsigned int, const std::string&...);
    FunctionLogObserver (const Callback&, unsigned int, const std::string&...);
    ~FunctionLogObserver () = default;

    FunctionLogObserver (FunctionLogObserver&&) = default;
    FunctionLogObserver& operator = (FunctionLogObserver&&) = default;

    FunctionLogObserver (const FunctionLogObserver&) = default;
    FunctionLogObserver& operator = (const FunctionLogObserver&) = default;

    const std::vector<Callback>& getCallbacks () const;
    void setCallbacks (const std::vector<Callback>&);
    void addCallback (const Callback&...);
    void clearCallbacks ();

protected:

    virtual void notifyCallback (LogLevel, const std::string&, const std::string&);

    std::mutex m_mutex;
    std::vector<Callback> m_callbacks;

};
}

#endif
