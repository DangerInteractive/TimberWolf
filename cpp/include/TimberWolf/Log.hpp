#ifndef TW_PKG_LOG
#define TW_PKG_LOG

/**
 * @file
 *
 * Auto-include header for the log subsystem. Included automatically by all
 * other packages. Represents the headers that are applicable to the log
 * subsystem. The headers included in the log package may only reference the
 * core package.
 */

#include "Core.hpp"

#include "Log/ConsoleLogObserver.hpp"
#include "Log/FileLogObserver.hpp"
#include "Log/FunctionLogObserver.hpp"
#include "Log/LogLevel.hpp"
#include "Log/LogObserver.hpp"

#endif
