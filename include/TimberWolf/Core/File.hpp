#ifndef TW_CLASS_FILE
#define TW_CLASS_FILE

/**
 * @file
 *
 * Header file for the tw::File class.
 */

#include <string>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <mutex>

namespace tw {
class File {

public:

    static inline constexpr std::ios_base::openmode ENABLE_READ =   std::ios::in;
    static inline constexpr std::ios_base::openmode ENABLE_WRITE =  std::ios::out;
    static inline constexpr std::ios_base::openmode ENABLE_APPEND = std::ios::app;
    static inline constexpr std::ios_base::openmode ENABLE_AT_END = std::ios::ate;
    static inline constexpr std::ios_base::openmode ENABLE_BINARY = std::ios::binary;
    static inline constexpr std::ios_base::openmode ENABLE_WIPE =   std::ios::trunc;

    File () = default;

    explicit File (const std::string&);
    File (const std::string&, std::ios_base::openmode);

    std::string readString ();

    template <typename ...T>
    bool write (T&&... data) {

        std::unique_lock<std::mutex> lock(m_fstream_mutex);

        if (!isOpen()) {
            return false;
        }

        if (!writeEnabled()) {
            return false;
        }

        (m_fstream << ... << std::forward<T>(data));

        return true;

    }

    template <typename ...T>
    bool writeLine (T&&... data) {

        std::unique_lock<std::mutex> lock(m_fstream_mutex);

        if (!isOpen()) {
            return false;
        }

        if (!writeEnabled()) {
            return false;
        }

        (m_fstream << ... << std::forward<T>(data)) << std::endl;

        return true;

    }

    bool isOpen () const;
    bool open ();
    bool close ();

    std::string getPath () const;
    bool setPath (const std::string&);

    bool readEnabled () const;
    bool enableRead ();
    bool disableRead ();
    bool writeEnabled () const;
    bool enableWrite ();
    bool disableWrite ();
    bool appendEnabled () const;
    bool enableAppend ();
    bool disableAppend ();
    bool atEndEnabled () const;
    bool enableAtEnd ();
    bool disableAtEnd ();
    bool binaryEnabled () const;
    bool enableBinary ();
    bool disableBinary ();
    bool wipeEnabled () const;
    bool enableWipe ();
    bool disableWipe ();

private:

    std::mutex m_metadata_mutex;
    std::string m_path {"./undefined.txt"};
    std::ios_base::openmode m_flags {ENABLE_READ};

    std::mutex m_fstream_mutex;
    std::fstream m_fstream;

};
}

#endif
