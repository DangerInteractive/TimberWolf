#include "../include/File.hpp"

tw::File::File (const std::string& path)
: m_path(path) {}

tw::File::File (const std::string& path, std::ios_base::openmode openFlags)
: m_path(path), m_flags(openFlags) {}

bool tw::File::isOpen () const {

    return m_fstream.is_open();

}

std::string tw::File::readString () {

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

bool tw::File::open () {

    std::scoped_lock lock(m_metadata_mutex, m_fstream_mutex);

    if (isOpen()) {
        return true;
    }

    m_fstream.open(m_path, m_flags);

    return isOpen();

}

bool tw::File::close () {

    std::scoped_lock lock(m_metadata_mutex, m_fstream_mutex);

    if (!isOpen()) {
        return true;
    }

    m_fstream.close();

    return !isOpen();

}

std::string tw::File::getPath () const {

    return m_path;

}

bool tw::File::setPath (const std::string& path) {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_path = path;

    return true;

}

bool tw::File::readEnabled () const {

    return m_flags & ENABLE_READ;

}

bool tw::File::enableRead () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags |= ENABLE_READ;

    return true;

}

bool tw::File::disableRead () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags &= ~ENABLE_READ;

    return true;

}

bool tw::File::writeEnabled () const {

    return m_flags & ENABLE_WRITE;

}

bool tw::File::enableWrite () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags |= ENABLE_WRITE;

    return true;

}

bool tw::File::disableWrite () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags &= ~ENABLE_WRITE;

    return true;

}

bool tw::File::appendEnabled () const {

    return m_flags & ENABLE_APPEND;

}

bool tw::File::enableAppend () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags |= ENABLE_APPEND;

    return true;

}

bool tw::File::disableAppend () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags &= ~ENABLE_APPEND;

    return true;

}

bool tw::File::atEndEnabled () const {

    return m_flags & ENABLE_AT_END;

}

bool tw::File::enableAtEnd () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags |= ENABLE_AT_END;

    return true;

}

bool tw::File::disableAtEnd () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags &= ~ENABLE_AT_END;

    return true;

}

bool tw::File::binaryEnabled () const {

    return m_flags & ENABLE_BINARY;

}

bool tw::File::enableBinary () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags |= ENABLE_BINARY;

    return true;

}

bool tw::File::disableBinary () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags &= ~ENABLE_BINARY;

    return true;

}

bool tw::File::wipeEnabled () const {

    return m_flags & ENABLE_WIPE;

}

bool tw::File::enableWipe () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags |= ENABLE_WIPE;

    return true;

}

bool tw::File::disableWipe () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags &= ~ENABLE_WIPE;

    return true;

}
