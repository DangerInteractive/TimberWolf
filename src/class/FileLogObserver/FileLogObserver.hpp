#ifndef H_CLASS_FILELOGOBSERVER
#define H_CLASS_FILELOGOBSERVER

#include <string>
#include <set>
#include <ctime>
#include <iomanip>
#include "../LogObserver/LogObserver.hpp"
#include "../File/File.hpp"

class FileLogObserver : public LogObserver {

public:

    FileLogObserver () = default;
    explicit FileLogObserver (unsigned int);
    explicit FileLogObserver (const std::set<std::string>&);
    explicit FileLogObserver (const std::string&...);
    FileLogObserver (unsigned int, const std::set<std::string>&);
    FileLogObserver (unsigned int, const std::string&...);
    ~FileLogObserver () override = default;

    FileLogObserver (FileLogObserver&&) = default;
    FileLogObserver& operator = (FileLogObserver&&) = default;

    FileLogObserver (const FileLogObserver&) = default;
    FileLogObserver& operator = (const FileLogObserver&) = default;

protected:

    virtual void notifyCallback (LogLevel, const std::string&, const std::string&) override;

    virtual std::string formatMessage (LogLevel, const std::string&, const std::string&);

    File m_file {"./log.txt", File::ENABLE_WRITE | File::ENABLE_APPEND};

};

#endif
