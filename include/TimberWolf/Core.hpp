#ifndef H_PKG_TW_CORE
#define H_PKG_TW_CORE

/**
 * @file
 *
 * Auto-include header for the core headers. Included automatically by all other
 * packages. Represents the universally-applicable headers that are likely to be
 * used frequently throughout the code. No headers included in the core package
 * are allowed to reference any other package.
 */

#include "Core/Clock.hpp"
#include "Core/Color.hpp"
#include "Core/Console.hpp"
#include "Core/File.hpp"
#include "Core/SpeedGovernor.hpp"
#include "Core/ThreadManager.hpp"

#endif
