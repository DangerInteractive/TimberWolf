#ifndef H_CLASS_FILELOGOBSERVER
#define H_CLASS_FILELOGOBSERVER

#include <string>
#include <set>
#include <ctime>
#include <iomanip>
#include "../LogObserver/LogObserver.hpp"
#include "../File/File.hpp"

namespace tw {
class FileLogObserver : public LogObserver {

public:

    FileLogObserver () = default;
    explicit FileLogObserver (const std::string&);
    FileLogObserver (const std::string&, unsigned int);
    FileLogObserver (const std::string&, const std::set<std::string>&);
    FileLogObserver (const std::string&, const std::string&...);
    FileLogObserver (const std::string&, unsigned int, const std::set<std::string>&);
    FileLogObserver (const std::string&, unsigned int, const std::string&...);
    ~FileLogObserver () override = default;

    FileLogObserver (FileLogObserver&&) = default;
    FileLogObserver& operator = (FileLogObserver&&) = default;

    FileLogObserver (const FileLogObserver&) = default;
    FileLogObserver& operator = (const FileLogObserver&) = default;

    std::string getFilePath () const;
    bool setFilePath (const std::string&);

protected:

    virtual void notifyCallback (LogLevel, const std::string&, const std::string&) override;

    virtual std::string formatMessage (LogLevel, const std::string&, const std::string&);

    File m_file {"./log.txt", File::ENABLE_WRITE | File::ENABLE_APPEND};

};
}

#endif
