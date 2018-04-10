#include "File.hpp"

File::File (const std::string& path)
: m_path(path) {}

File::File (const std::string& path, std::ios_base::openmode openFlags)
: m_path(path), m_flags(openFlags) {}

bool File::isOpen () const {

    return m_fstream.is_open();

}

std::string File::readString () {

    std::unique_lock<std::mutex> fstream_lock(m_fstream_mutex);

    if (!isOpen()) {
        return NULL;
    }

    if (!readEnabled()) {
        return NULL;
    }

    std::ostringstream oss;
    oss << m_fstream.rdbuf();
    return oss.str();

}

bool File::open () {

    std::scoped_lock lock(m_metadata_mutex, m_fstream_mutex);

    if (isOpen()) {
        return true;
    }

    m_fstream.open(m_path, m_flags);

    return isOpen();

}

bool File::close () {

    std::scoped_lock lock(m_metadata_mutex, m_fstream_mutex);

    if (!isOpen()) {
        return true;
    }

    m_fstream.close();

    return !isOpen();

}

std::string File::getPath () const {

    return m_path;

}

bool File::setPath (const std::string& path) {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_path = path;

    return true;

}

bool File::readEnabled () const {

    return m_flags & ENABLE_READ;

}

bool File::enableRead () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags |= ENABLE_READ;

    return true;

}

bool File::disableRead () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags &= ~ENABLE_READ;

    return true;

}

bool File::writeEnabled () const {

    return m_flags & ENABLE_WRITE;

}

bool File::enableWrite () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags |= ENABLE_WRITE;

    return true;

}

bool File::disableWrite () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags &= ~ENABLE_WRITE;

    return true;

}

bool File::appendEnabled () const {

    return m_flags & ENABLE_APPEND;

}

bool File::enableAppend () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags |= ENABLE_APPEND;

    return true;

}

bool File::disableAppend () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags &= ~ENABLE_APPEND;

    return true;

}

bool File::atEndEnabled () const {

    return m_flags & ENABLE_AT_END;

}

bool File::enableAtEnd () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags |= ENABLE_AT_END;

    return true;

}

bool File::disableAtEnd () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags &= ~ENABLE_AT_END;

    return true;

}

bool File::binaryEnabled () const {

    return m_flags & ENABLE_BINARY;

}

bool File::enableBinary () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags |= ENABLE_BINARY;

    return true;

}

bool File::disableBinary () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags &= ~ENABLE_BINARY;

    return true;

}

bool File::wipeEnabled () const {

    return m_flags & ENABLE_WIPE;

}

bool File::enableWipe () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags |= ENABLE_WIPE;

    return true;

}

bool File::disableWipe () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags &= ~ENABLE_WIPE;

    return true;

}
