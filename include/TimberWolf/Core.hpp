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
#include "Core/GlobalVertex.hpp"
#include "Core/Gradient.hpp"
#include "Core/Math.hpp"
#include "Core/Matrix3.hpp"
#include "Core/Matrix3Double.hpp"
#include "Core/Matrix4.hpp"
#include "Core/Matrix4Double.hpp"
#include "Core/Projection.hpp"
#include "Core/Quaternion.hpp"
#include "Core/QuaternionDouble.hpp"
#include "Core/Rotation.hpp"
#include "Core/SpeedGovernor.hpp"
#include "Core/Transformation.hpp"
#include "Core/Vector2.hpp"
#include "Core/Vector2Double.hpp"
#include "Core/Vector3.hpp"
#include "Core/Vector3Double.hpp"
#include "Core/Vertex.hpp"

#endif
