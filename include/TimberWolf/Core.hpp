#ifndef TW_PKG_CORE
#define TW_PKG_CORE

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
#include "Core/Gradient.hpp"
#include "Core/Rotation.hpp"
#include "Core/SpeedGovernor.hpp"
#include "Core/ThreadManager.hpp"
#include "Core/Vertex.hpp"

#endif
