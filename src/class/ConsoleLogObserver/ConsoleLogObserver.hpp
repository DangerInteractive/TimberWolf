#ifndef H_CLASS_CONSOLELOGOBSERVER
#define H_CLASS_CONSOLELOGOBSERVER

#include <string>
#include <set>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "../LogObserver/LogObserver.hpp"
#include "../Console/Console.hpp"

class ConsoleLogObserver : public LogObserver {

public:

    ConsoleLogObserver () = default;
    explicit ConsoleLogObserver (unsigned int);
    explicit ConsoleLogObserver (const std::set<std::string>&);
    explicit ConsoleLogObserver (const std::string&...);
    ConsoleLogObserver (unsigned int, const std::set<std::string>&);
    ConsoleLogObserver (unsigned int, const std::string&...);
    virtual ~ConsoleLogObserver () override = default;

    ConsoleLogObserver (ConsoleLogObserver&&) = default;
    ConsoleLogObserver& operator = (ConsoleLogObserver&&) = default;

    ConsoleLogObserver (const ConsoleLogObserver&) = default;
    ConsoleLogObserver& operator = (const ConsoleLogObserver&) = default;

protected:

    virtual void notifyCallback (LogLevel, const std::string&, const std::string&) override;

    virtual std::string formatMessage (LogLevel, const std::string&, const std::string&) const;

};

#endif
