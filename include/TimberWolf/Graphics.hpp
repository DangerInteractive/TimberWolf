#ifndef TW_PKG_GRAPHICS
#define TW_PKG_GRAPHICS

/**
 * @file
 *
 * Auto-include header for the graphics subsystem. Represents the headers that
 * are applicable to the graphics rendering subsystem, not including the
 * graphics API backends themselves, which are separate packages. The headers
 * included in the graphics package may reference the core, log, and window
 * packages.
 */

#include "Core.hpp"
#include "Log.hpp"
#include "Window.hpp"

#include "Graphics/Camera.hpp"
#include "Graphics/GraphicsBufferable.hpp"
#include "Graphics/Material.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/Model.hpp"
#include "Graphics/Puppet.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Scene.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/TexturePoint.hpp"
#endif
