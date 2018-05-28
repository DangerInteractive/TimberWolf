#ifndef H_TW_LOGLEVEL
#define H_TW_LOGLEVEL

/**
 * @file
 *
 * Header file for the tw::LogLevel enum.
 */

namespace tw {
enum LogLevel {
    UNDEFINED = 0,
    VERBOSE = 1,
    NOTICE = 2,
    WARNING = 3,
    ERROR = 4
};
}

#endif