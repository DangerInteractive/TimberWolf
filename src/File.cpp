#include "../include/File.hpp"

/**
 * @class tw::File
 *
 * Handle for an operating system file, providing manipulation and data access.
 */

/**
 * Constructor taking in a std::string of the path to the file.
 *
 * @param path file path
 */
tw::File::File (const std::string& path)
: m_path(path) {}

/**
 * Constructor taking in a std::string of the path to the file and file opening
 * flags.
 *
 * @param path      file path
 * @param openFlags file opening flags
 */
tw::File::File (const std::string& path, std::ios_base::openmode openFlags)
: m_path(path), m_flags(openFlags) {}

/**
 * Check if the file is open.
 *
 * @return true if file is open, false if not
 */
bool tw::File::isOpen () const {

    return m_fstream.is_open();

}

/**
 * Read the contents of the file as a std::string.
 *
 * @return file contents
 */
std::string tw::File::readString () {

    std::unique_lock<std::mutex> fstream_lock(m_fstream_mutex);

    if (!isOpen()) {
        if (!open()) {
            return "";
        }
    }

    if (!readEnabled()) {
        return "";
    }

    std::ostringstream oss;
    oss << m_fstream.rdbuf();
    return oss.str();

}

/**
 * Open the file for reading and/or editing, depending on the enabled flags.
 *
 * @return true if file is opened successfully, false if not
 */
bool tw::File::open () {

    std::scoped_lock lock(m_metadata_mutex, m_fstream_mutex);

    if (isOpen()) {
        return true;
    }

    m_fstream.open(m_path, m_flags);

    return isOpen();

}

/**
 * Close the file handle, freeing the filesystem handle resource.
 *
 * @return true if file is closed successfully, false if not
 */
bool tw::File::close () {

    std::scoped_lock lock(m_metadata_mutex, m_fstream_mutex);

    if (!isOpen()) {
        return true;
    }

    m_fstream.close();

    return !isOpen();

}

/**
 * Get the path of the file as a std::string.
 *
 * @return file path
 */
std::string tw::File::getPath () const {

    return m_path;

}

/**
 * Set the path of the file as a std::string. Only works if the file is not
 * currently open.
 *
 * @param path file path
 * @return true if path is set successfully, false if not
 */
bool tw::File::setPath (const std::string& path) {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_path = path;

    return true;

}

/**
 * Check if reading from the file is enabled.
 *
 * @return true if reading is enabled, false if not
 */
bool tw::File::readEnabled () const {

    return m_flags & ENABLE_READ;

}

/**
 * Enable reading from the file. Only works if the file is not currently open.
 *
 * @return true if reading is successfully enabled, false if not
 */
bool tw::File::enableRead () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags |= ENABLE_READ;

    return true;

}

/**
 * Disable reading from the file. Only works if the file is not currently open.
 *
 * @return true if reading is successfully diabled, false if not
 */
bool tw::File::disableRead () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags &= ~ENABLE_READ;

    return true;

}

/**
 * Check if writing to the file is enabled.
 *
 * @return true if wrtiting is enabled, false if not
 */
bool tw::File::writeEnabled () const {

    return m_flags & ENABLE_WRITE;

}

/**
 * Enable writing to the file. Only works if the file is not currently open.
 *
 * @return true if writing is successfully enabled, false if not
 */
bool tw::File::enableWrite () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags |= ENABLE_WRITE;

    return true;

}

/**
 * Disable writing to the file. Only works if the file is not currently open.
 *
 * @return true if writing is successfully disabled, false if not
 */
bool tw::File::disableWrite () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags &= ~ENABLE_WRITE;

    return true;

}

/**
 * Check if appending to the end of the file on each write, as opposed to the
 * default behavior of overwriting the file on each write, is enabled.
 *
 * @return true if file will be appended, false if file will be overwritten
 */
bool tw::File::appendEnabled () const {

    return m_flags & ENABLE_APPEND;

}

/**
 * Enable appending to the end of the file on each write, as opposed to the
 * default behavior of overwriting the file on each write. Only works if the
 * file is not currently open.
 *
 * @return true if appending is successfully enabled, false if not
 */
bool tw::File::enableAppend () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags |= ENABLE_APPEND;

    return true;

}

/**
 * Disable appending to the end of the file on each write, causing the file to
 * instead be overwritten on each write. Only works if the file is not currently
 * open.
 *
 * @return true if appending is successfully disabled, false if not
 */
bool tw::File::disableAppend () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags &= ~ENABLE_APPEND;

    return true;

}

/**
 * Check if starting iteration at the end of the file, as opposed to the default
 * behavior of starting iteration at the beginning of the file, is enabled.
 *
 * @return true if file will start at end, false if file will start at start
 */
bool tw::File::atEndEnabled () const {

    return m_flags & ENABLE_AT_END;

}

/**
 * Enable starting iteration at the end of the file, as opposed to the default
 * behavior of starting iteration at the beginning of the file. Only works if
 * the file is not currently opened.
 *
 * @return true if starting at end is successfully enabled, false if not
 */
bool tw::File::enableAtEnd () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags |= ENABLE_AT_END;

    return true;

}

/**
 * Disable starting iteration at the end of the file, causing iteration of the
 * file to begin at the start of the file instead of the end. Only works if the
 * file is not currently opened.
 *
 * @return true if starting at end is successfully disabled, false if not
 */
bool tw::File::disableAtEnd () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags &= ~ENABLE_AT_END;

    return true;

}

/**
 * Check if opening the file as binary data, as opposed to the default behavior
 * of opening the file as text data.
 *
 * @return true if file will open as binary, true if file will open as text.
 */
bool tw::File::binaryEnabled () const {

    return m_flags & ENABLE_BINARY;

}

/**
 * Enable opening the file as binary data, as opposed to the default behavior of
 * of opening the file as text data. Only works if the file is not currently
 * open.
 *
 * @return true if binary mode is successfully enabled, false if not
 */
bool tw::File::enableBinary () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags |= ENABLE_BINARY;

    return true;

}

/**
 * Disable opening the file as binary data, causing the file to be opened as
 * text data. Only works if the file is not currently open.
 *
 * @return true if binary mode is successfully diabled, false if not
 */
bool tw::File::disableBinary () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags &= ~ENABLE_BINARY;

    return true;

}

/**
 * Check if wiping file contents on opening is enabled, as opposed to the
 * default behavior of waiting for a write to make modifications.
 *
 * @return true if file will be wiped on opening, false if modifications wait for write
 */
bool tw::File::wipeEnabled () const {

    return m_flags & ENABLE_WIPE;

}

/**
 * Enable wiping the file contents on opening, as opposed to the default
 * behavior of waiting for a write to make modifications. Only works if the file
 * is not currently open.
 *
 * @return true if wipe on open is successfully enabled, false if not
 */
bool tw::File::enableWipe () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags |= ENABLE_WIPE;

    return true;

}

/**
 * Disable wiping the file contents on opening, causing the file to wait for
 * a write to make any modifications to contents. Note that if append is not
 * enabled, a write operation will still overwrite the file. Only works if the
 * file is not currently open.
 *
 * @return true if wipe on open is successfully diabled, false if not
 */
bool tw::File::disableWipe () {

    std::unique_lock<std::mutex> metadata_lock(m_metadata_mutex);

    if (isOpen()) {
        return false;
    }

    m_flags &= ~ENABLE_WIPE;

    return true;

}
