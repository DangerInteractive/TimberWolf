cmake_minimum_required (VERSION 3.10)

# installation setup
set (INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set (INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set (INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")
if (WIN32 AND NOT CYGWIN)
    set (DEF_INSTALL_CMAKE_DIR CMake)
else ()
    set (DEF_INSTALL_CMAKE_DIR lib/CMake/TimberWolf)
endif ()
set (INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")

# Make relative paths absolute
foreach (p LIB BIN INCLUDE CMAKE)
    set (var INSTALL_${p}_DIR)
    if (NOT IS_ABSOLUTE "${${var}}")
        set (${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
    endif ()
endforeach ()

# build type selection
if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug, Release, ReleaseNative, ReleaseCompact)" FORCE)
endif ()

# notify of the build type in use
message (STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

# project definition
set (LIBTIMBERWOLF_VERSION_MAJOR 0)
set (LIBTIMBERWOLF_VERSION_MINOR 0)
set (LIBTIMBERWOLF_VERSION_PATCH 0)
project (
    TimberWolf
    VERSION ${LIBTIMBERWOLF_VERSION_MAJOR}.${LIBTIMBERWOLF_VERSION_MINOR}.${LIBTIMBERWOLF_VERSION_PATCH}
    DESCRIPTION "high-performance C++ OpenGL/Vulkan game engine"
)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fstack-protector -Wl,-z,relro -Wl,-z,now -Werror -Wall -Wextra -Wpointer-arith -Wformat-security -Wformat -Wreturn-type -Wsign-compare -Wmultichar -Wformat-nonliteral -Winit-self -Wuninitialized -Wreturn-local-addr -Wno-unused-parameter -Wno-unused-function -Wno-unused-label")
set (CMAKE_CXX_FLAGS_DEBUG_ORIGINAL "${CMAKE_CXX_FLAGS_DEBUG}")
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -march=core2 -mtune=generic")
set (CMAKE_CXX_FLAGS_RELEASE_ORIGINAL "${CMAKE_CXX_FLAGS_RELEASE}")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=core2 -mtune=generic")
set (CMAKE_CXX_FLAGS_RELEASENATIVE "${CMAKE_CXX_FLAGS_RELEASE_ORIGINAL} -O3 -march=native")
set (CMAKE_CXX_FLAGS_RELEASECOMPACT "${CMAKE_CXX_FLAGS_RELEASE_ORIGINAL} -Os -march=core2 -mtune=generic")
set (LIBTIMBERWOLF_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/TimberWolf)
set (LIBTIMBERWOLF_PUBLIC_HEADER ${PROJECT_SOURCE_DIR}/include)
set (LIBTIMBERWOLF_SOURCE_DIR ${PROJECT_SOURCE_DIR}/source/TimberWolf)
configure_file (
    ${PROJECT_SOURCE_DIR}/TimberWolf.hpp.in
    ${LIBTIMBERWOLF_INCLUDE_DIR}/TimberWolf.hpp
)
include_directories (
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

# documentation
configure_file (
    ${PROJECT_SOURCE_DIR}/Doxyfile.in
    ${PROJECT_SOURCE_DIR}/Doxyfile
    @ONLY
)

# list of sources (just for compilation)
list (APPEND SOURCES

    # Bundled Libraries
    ${LIBTIMBERWOLF_SOURCE_DIR}/External/FastNoise/FastNoise.cpp

    # Engine Core Classes
    ${LIBTIMBERWOLF_SOURCE_DIR}/Core/Clock.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Core/Color.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Core/Console.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Core/File.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Core/Gradient.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Core/Projection.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Core/Rotation.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Core/SpeedGovernor.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Core/Transformation.cpp

    # Engine Log Subsystem
    ${LIBTIMBERWOLF_SOURCE_DIR}/Log/ConsoleLogObserver.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Log/FileLogObserver.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Log/FunctionLogObserver.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Log/Log.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Log/LogObserver.cpp

    # Engine Game Loop Subsystem
    ${LIBTIMBERWOLF_SOURCE_DIR}/GameLoop/Controller.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/GameLoop/GameLoop.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/GameLoop/GameState.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/GameLoop/GameStateManager.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/GameLoop/GameStateStore.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/GameLoop/Keybinding.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/GameLoop/KeyMod.cpp

    # Engine Graphics Subsystem
    ${LIBTIMBERWOLF_SOURCE_DIR}/Graphics/Camera.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Graphics/GraphicsBufferable.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Graphics/Material.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Graphics/Mesh.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Graphics/Model.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Graphics/Puppet.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Graphics/Renderer.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Graphics/Scene.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Graphics/Texture.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Graphics/TexturePoint.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Graphics/VertexSet.cpp

    # Engine OpenGL Graphics Backend
    ${LIBTIMBERWOLF_SOURCE_DIR}/Graphics/OpenGL/GLComputeShader.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Graphics/OpenGL/GLFragmentShader.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Graphics/OpenGL/GLGeometryShader.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Graphics/OpenGL/GLRenderer.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Graphics/OpenGL/GLShader.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Graphics/OpenGL/GLShaderProgram.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Graphics/OpenGL/GLShaderStore.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Graphics/OpenGL/GLTesselationControlShader.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Graphics/OpenGL/GLTesselationEvaluationShader.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Graphics/OpenGL/GLVertexArray.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Graphics/OpenGL/GLVertexBuffer.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/Graphics/OpenGL/GLVertexShader.cpp

    # Engine Window Subsystem
    ${LIBTIMBERWOLF_SOURCE_DIR}/Window/Window.cpp

    # Engine World Subsystem
    ${LIBTIMBERWOLF_SOURCE_DIR}/World/Entity.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/World/EntityComponent.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/World/PhysicsEntityComponent.cpp
    ${LIBTIMBERWOLF_SOURCE_DIR}/World/World.cpp

)

set_source_files_properties(
    ${LIBTIMBERWOLF_SOURCE_DIR}/External/FastNoise/FastNoise.cpp
    PROPERTIES COMPILE_FLAGS
        "-Wno-implicit-fallthrough -Wno-maybe-uninitialized -Wno-strict-aliasing" # lots of warnings in this library, but that's not our problem
)

# list of header files (the public API)
list (APPEND HEADERS

    # Library Metadata
    ${LIBTIMBERWOLF_INCLUDE_DIR}/TimberWolf.hpp

    # Bundled Libraries
    ${LIBTIMBERWOLF_INCLUDE_DIR}/External/FastNoise.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/External/FastNoise/FastNoise.h

    # Engine Auto-Include Headers
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Core.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/External.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/GameLoop.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Graphics.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Log.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/OpenGL.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Window.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/World.hpp

    # Engine Core Classes
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Core/Clock.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Core/Color.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Core/Console.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Core/File.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Core/GlobalVertex.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Core/Gradient.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Core/Math.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Core/Matrix3.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Core/Matrix3Double.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Core/Matrix4.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Core/Matrix4Double.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Core/Quaternion.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Core/QuaternionDouble.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Core/Projection.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Core/Rotation.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Core/SpeedGovernor.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Core/Transformation.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Core/Vector2.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Core/Vector2Double.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Core/Vector3.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Core/Vector3Double.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Core/Vertex.hpp

    # Engine Log Subsystem
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Log/ConsoleLogObserver.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Log/FileLogObserver.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Log/FunctionLogObserver.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Log/Log.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Log/LogObserver.hpp

    # Engine Game Loop Subsystem
    ${LIBTIMBERWOLF_INCLUDE_DIR}/GameLoop/Controller.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/GameLoop/GameLoop.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/GameLoop/GameState.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/GameLoop/GameStateManager.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/GameLoop/GameStateStore.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/GameLoop/Keybinding.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/GameLoop/KeyMod.hpp

    # Engine Graphics Subsystem
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Graphics/Camera.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Graphics/GraphicsBufferable.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Graphics/Material.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Graphics/Mesh.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Graphics/Model.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Graphics/Puppet.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Graphics/Renderer.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Graphics/Scene.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Graphics/Texture.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Graphics/TexturePoint.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Graphics/VertexSet.hpp

    # Engine OpenGL Graphics Backend
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Graphics/OpenGL/GLComputeShader.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Graphics/OpenGL/GLFragmentShader.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Graphics/OpenGL/GLGeometryShader.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Graphics/OpenGL/GLRenderer.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Graphics/OpenGL/GLShader.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Graphics/OpenGL/GLShaderProgram.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Graphics/OpenGL/GLShaderStore.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Graphics/OpenGL/GLTesselationControlShader.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Graphics/OpenGL/GLTesselationEvaluationShader.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Graphics/OpenGL/GLVertexArray.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Graphics/OpenGL/GLVertexBuffer.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Graphics/OpenGL/GLVertexShader.hpp

    # Engine Window Subsystem
    ${LIBTIMBERWOLF_INCLUDE_DIR}/Window/Window.hpp

    # Engine World Subsystem
    ${LIBTIMBERWOLF_INCLUDE_DIR}/World/Entity.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/World/EntityComponent.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/World/PhysicsEntityComponent.hpp
    ${LIBTIMBERWOLF_INCLUDE_DIR}/World/World.hpp

)

# library output
set (LIBRARY_NAME "TimberWolf")
add_library (${LIBRARY_NAME} SHARED ${SOURCES})
set_target_properties (${LIBRARY_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties (${LIBRARY_NAME} PROPERTIES SOVERSION ${LIBTIMBERWOLF_VERSION_MAJOR})
set_target_properties (${LIBRARY_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
configure_file (
    ${PROJECT_SOURCE_DIR}/TimberWolf.pc.in
    ${PROJECT_BINARY_DIR}/TimberWolf.pc
    @ONLY
)

# find_package stuff
export (
    TARGETS ${LIBRARY_NAME}
    FILE ${PROJECT_BINARY_DIR}/TimberWolfTargets.cmake
)
export (PACKAGE TimberWolf)
file (RELATIVE_PATH REL_INCLUDE_DIR ${INSTALL_CMAKE_DIR}
    ${INSTALL_INCLUDE_DIR}
)
set (CONF_INCLUDE_DIRS
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_BINARY_DIR}"
)
configure_file (
    ${PROJECT_SOURCE_DIR}/TimberWolfConfig.cmake.in
    ${PROJECT_BINARY_DIR}/TimberWolfConfig.cmake
    @ONLY
)
set (CONF_INCLUDE_DIRS
    "\${LIBTIMBERWOLF_CMAKE_DIR}/${REL_INCLUDE_DIR}"
)
configure_file (
    ${PROJECT_SOURCE_DIR}/TimberWolfConfig.cmake.in
    ${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/TimberWolfConfig.cmake
    @ONLY
)
configure_file (
    ${PROJECT_SOURCE_DIR}/TimberWolfConfigVersion.cmake.in
    ${PROJECT_BINARY_DIR}/TimberWolfConfigVersion.cmake
    @ONLY
)

# dependencies
set (CMAKE_THREAD_PREFER_PTHREAD TRUE)
set (THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package (Threads REQUIRED)
set (OpenGL_GL_PREFERENCE "GLVND")
find_package (OpenGL REQUIRED)
find_package (GLEW REQUIRED)
find_package (glfw3 REQUIRED)
find_package (glm REQUIRED)
include_directories (${OPENGL_INCLUDE_DIR})
target_link_libraries (${LIBRARY_NAME}
    Threads::Threads
    ${OPENGL_gl_LIBRARY}
    glfw
    GLEW
    glm
)

# installation
include (GNUInstallDirs)
install (TARGETS ${LIBRARY_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install (
    DIRECTORY ${LIBTIMBERWOLF_PUBLIC_HEADER}/ # trailing slash intended, don't remove
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install (
    FILES ${CMAKE_BINARY_DIR}/TimberWolf.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)
install (
    FILES
        ${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/TimberWolfConfig.cmake
        ${PROJECT_BINARY_DIR}/TimberWolfConfigVersion.cmake
    DESTINATION ${INSTALL_CMAKE_DIR}
    COMPONENT dev
)

# packaging
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE ${PROJECT_SOURCE_DIR}/LICENSE)
set (CPACK_RESOURCE_VERSION_MAJOR ${LIBTIMBERWOLF_VERSION_MAJOR})
set (CPACK_RESOURCE_VERSION_MINOR ${LIBTIMBERWOLF_VERSION_MINOR})
set (CPACK_RESOURCE_VERSION_PATCH ${LIBTIMBERWOLF_VERSION_PATCH})
include (CPack)
