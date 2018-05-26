#ifndef H_PKG_TW_OPENGL
#define H_PKG_TW_OPENGL

/**
 * @file
 *
 * Auto-include header for the OpenGL graphics backend. Represents the graphics
 * rendering backend using the OpenGL API. The headers included in the OpenGL
 * package may reference the core, log, graphics, and window packages.
 */

#include "Core.hpp"
#include "Log.hpp"
#include "Graphics.hpp"
#include "Window.hpp"

#include "Graphics/OpenGL/ComputeShader.hpp"
#include "Graphics/OpenGL/FragmentShader.hpp"
#include "Graphics/OpenGL/GeometryShader.hpp"
#include "Graphics/OpenGL/Shader.hpp"
#include "Graphics/OpenGL/ShaderProgram.hpp"
#include "Graphics/OpenGL/ShaderStore.hpp"
#include "Graphics/OpenGL/TesselationControlShader.hpp"
#include "Graphics/OpenGL/TesselationEvaluationShader.hpp"
#include "Graphics/OpenGL/VertexArray.hpp"
#include "Graphics/OpenGL/VertexBuffer.hpp"
#include "Graphics/OpenGL/VertexShader.hpp"

#endif
