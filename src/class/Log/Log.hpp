#ifndef H_CLASS_LOG
#define H_CLASS_LOG

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <mutex>
#include <exception>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../enum/LogLevel/LogLevel.hpp"

class Log {

public:

    Log () = delete; // static only
    ~Log () = delete;

    Log (Log&&) = delete;
    Log& operator = (Log&&) = delete;

    Log (const Log&) = delete;
    Log& operator = (const Log&) = delete;

    static LogLevel getFilterLevel ();
    static void setFilterLevel (const LogLevel);

    static void log (const std::string, const LogLevel = LogLevel::VERBOSE);

    static void verbose (const std::string);
    static void notice  (const std::string);
    static void warning (const std::string);
    static void error   (const std::string);

    static void bindCallbacks ();

    static void unhandledException ();
    static void glfwError (int, const char*);
    static void glewError (GLenum);

private:

    static std::string formatMessage (const std::string, const LogLevel = LogLevel::VERBOSE);

    static LogLevel m_filterLevel;

    static std::mutex mutex_out;

};

#endif
