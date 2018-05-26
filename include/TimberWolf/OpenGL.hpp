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

#include "Graphics/OpenGL/GLComputeShader.hpp"
#include "Graphics/OpenGL/GLFragmentShader.hpp"
#include "Graphics/OpenGL/GLGeometryShader.hpp"
#include "Graphics/OpenGL/GLShader.hpp"
#include "Graphics/OpenGL/GLShaderProgram.hpp"
#include "Graphics/OpenGL/GLShaderStore.hpp"
#include "Graphics/OpenGL/GLTesselationControlShader.hpp"
#include "Graphics/OpenGL/GLTesselationEvaluationShader.hpp"
#include "Graphics/OpenGL/GLVertexArray.hpp"
#include "Graphics/OpenGL/GLVertexBuffer.hpp"
#include "Graphics/OpenGL/GLVertexShader.hpp"

#endif
