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
    set (CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug, Release, Compact)" FORCE)
endif ()

# notify of the build type in use
message (STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

# project definition
set (TimberWolf_VERSION_MAJOR 0)
set (TimberWolf_VERSION_MINOR 0)
set (TimberWolf_VERSION_PATCH 0)
project (
    TimberWolf
    VERSION ${TimberWolf_VERSION_MAJOR}.${TimberWolf_VERSION_MINOR}.${TimberWolf_VERSION_PATCH}
    DESCRIPTION "high-performance C++ OpenGL/Vulkan game engine"
)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fstack-protector -Wl,-z,relro -Wl,-z,now -Wformat-security -W -Wall -Wno-unused-parameter -Wno-unused-function -Wno-unused-label -Wpointer-arith -Wformat -Wreturn-type -Wsign-compare -Wmultichar -Wformat-nonliteral -Winit-self -Wuninitialized -Wno-deprecated -Werror")
set (CMAKE_CXX_FLAGS_DEBUG "-g -Og")
set (CMAKE_CXX_FLAGS_RELEASE "-O3")
set (CMAKE_CXX_FLAGS_COMPACT "-Os")
set (TimberWolf_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/TimberWolf)
set (TimberWolf_PUBLIC_HEADER ${PROJECT_SOURCE_DIR}/include)
set (TimberWolf_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/TimberWolf)
configure_file (
    ${PROJECT_SOURCE_DIR}/TimberWolf.hpp.in
    ${TimberWolf_INCLUDE_DIR}/TimberWolf.hpp
)
include_directories (
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

# debug mode testing/analysis
unset (CMAKE_CXX_CPPCHECK CACHE)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message (STATUS "Testing/Analysis Enabled")
    find_program (CMAKE_CXX_CPPCHECK NAMES cppcheck)
    if (CMAKE_CXX_CPPCHECK)
        list (APPEND CMAKE_CXX_CPPCHECK
            "--enable=warning"
            "--inconclusive"
            "--force"
            "--inline-suppr"
        )
    else ()
        message (WARNING "Could not find CPPCheck executable. CPPCheck testing disabled.")
    endif ()
else ()
    message (STATUS "Testing/Analysis Disabled")
    set (CMAKE_CXX_CPPCHECK)
endif ()

# documentation
configure_file (
    ${PROJECT_SOURCE_DIR}/Doxyfile.in
    ${PROJECT_SOURCE_DIR}/Doxyfile
    @ONLY
)

# list of sources (just for compilation)
list (APPEND SOURCES

    # Bundled Libraries
    ${PROJECT_SOURCE_DIR}/lib/FastNoise/FastNoise.cpp

    # Engine Core Classes
    ${TimberWolf_SOURCE_DIR}/Core/Clock.cpp
    ${TimberWolf_SOURCE_DIR}/Core/Color.cpp
    ${TimberWolf_SOURCE_DIR}/Core/Console.cpp
    ${TimberWolf_SOURCE_DIR}/Core/File.cpp
    ${TimberWolf_SOURCE_DIR}/Core/Gradient.cpp
    ${TimberWolf_SOURCE_DIR}/Core/Projection.cpp
    ${TimberWolf_SOURCE_DIR}/Core/Rotation.cpp
    ${TimberWolf_SOURCE_DIR}/Core/SpeedGovernor.cpp
    ${TimberWolf_SOURCE_DIR}/Core/Transformation.cpp

    # Engine Log Subsystem
    ${TimberWolf_SOURCE_DIR}/Log/ConsoleLogObserver.cpp
    ${TimberWolf_SOURCE_DIR}/Log/FileLogObserver.cpp
    ${TimberWolf_SOURCE_DIR}/Log/FunctionLogObserver.cpp
    ${TimberWolf_SOURCE_DIR}/Log/Log.cpp
    ${TimberWolf_SOURCE_DIR}/Log/LogObserver.cpp

    # Engine Game Loop Subsystem
    ${TimberWolf_SOURCE_DIR}/GameLoop/Controller.cpp
    ${TimberWolf_SOURCE_DIR}/GameLoop/GameLoop.cpp
    ${TimberWolf_SOURCE_DIR}/GameLoop/GameState.cpp
    ${TimberWolf_SOURCE_DIR}/GameLoop/GameStateManager.cpp
    ${TimberWolf_SOURCE_DIR}/GameLoop/GameStateStore.cpp
    ${TimberWolf_SOURCE_DIR}/GameLoop/Keybinding.cpp
    ${TimberWolf_SOURCE_DIR}/GameLoop/KeyMod.cpp

    # Engine Graphics Subsystem
    ${TimberWolf_SOURCE_DIR}/Graphics/Camera.cpp
    ${TimberWolf_SOURCE_DIR}/Graphics/GraphicsBufferable.cpp
    ${TimberWolf_SOURCE_DIR}/Graphics/Material.cpp
    ${TimberWolf_SOURCE_DIR}/Graphics/Mesh.cpp
    ${TimberWolf_SOURCE_DIR}/Graphics/Model.cpp
    ${TimberWolf_SOURCE_DIR}/Graphics/Puppet.cpp
    ${TimberWolf_SOURCE_DIR}/Graphics/Renderer.cpp
    ${TimberWolf_SOURCE_DIR}/Graphics/Scene.cpp
    ${TimberWolf_SOURCE_DIR}/Graphics/Texture.cpp
    ${TimberWolf_SOURCE_DIR}/Graphics/TexturePoint.cpp
    ${TimberWolf_SOURCE_DIR}/Graphics/VertexSet.cpp

    # Engine OpenGL Graphics Backend
    ${TimberWolf_SOURCE_DIR}/Graphics/OpenGL/GLComputeShader.cpp
    ${TimberWolf_SOURCE_DIR}/Graphics/OpenGL/GLFragmentShader.cpp
    ${TimberWolf_SOURCE_DIR}/Graphics/OpenGL/GLGeometryShader.cpp
    ${TimberWolf_SOURCE_DIR}/Graphics/OpenGL/GLRenderer.cpp
    ${TimberWolf_SOURCE_DIR}/Graphics/OpenGL/GLShader.cpp
    ${TimberWolf_SOURCE_DIR}/Graphics/OpenGL/GLShaderProgram.cpp
    ${TimberWolf_SOURCE_DIR}/Graphics/OpenGL/GLShaderStore.cpp
    ${TimberWolf_SOURCE_DIR}/Graphics/OpenGL/GLTesselationControlShader.cpp
    ${TimberWolf_SOURCE_DIR}/Graphics/OpenGL/GLTesselationEvaluationShader.cpp
    ${TimberWolf_SOURCE_DIR}/Graphics/OpenGL/GLVertexArray.cpp
    ${TimberWolf_SOURCE_DIR}/Graphics/OpenGL/GLVertexBuffer.cpp
    ${TimberWolf_SOURCE_DIR}/Graphics/OpenGL/GLVertexShader.cpp

    # Engine Window Subsystem
    ${TimberWolf_SOURCE_DIR}/Window/Window.cpp

    # Engine World Subsystem
    ${TimberWolf_SOURCE_DIR}/World/Entity.cpp
    ${TimberWolf_SOURCE_DIR}/World/EntityComponent.cpp
    ${TimberWolf_SOURCE_DIR}/World/PhysicsEntityComponent.cpp
    ${TimberWolf_SOURCE_DIR}/World/World.cpp

)
set_source_files_properties(
    ${PROJECT_SOURCE_DIR}/lib/FastNoise/FastNoise.cpp
    PROPERTIES COMPILE_FLAGS
        "-Wno-implicit-fallthrough -Wno-maybe-uninitialized"
)

# list of header files (the public API)
list (APPEND HEADERS

    # Library Metadata
    ${TimberWolf_INCLUDE_DIR}/TimberWolf.hpp

    # Bundled Libraries
    ${PROJECT_SOURCE_DIR}/lib/FastNoise/FastNoise.h

    # Engine Auto-Include Headers
    ${TimberWolf_INCLUDE_DIR}/Core.hpp
    ${TimberWolf_INCLUDE_DIR}/GameLoop.hpp
    ${TimberWolf_INCLUDE_DIR}/Graphics.hpp
    ${TimberWolf_INCLUDE_DIR}/Log.hpp
    ${TimberWolf_INCLUDE_DIR}/OpenGL.hpp
    ${TimberWolf_INCLUDE_DIR}/Window.hpp
    ${TimberWolf_INCLUDE_DIR}/World.hpp

    # Engine Core Classes
    ${TimberWolf_INCLUDE_DIR}/Core/Clock.hpp
    ${TimberWolf_INCLUDE_DIR}/Core/Color.hpp
    ${TimberWolf_INCLUDE_DIR}/Core/Console.hpp
    ${TimberWolf_INCLUDE_DIR}/Core/File.hpp
    ${TimberWolf_INCLUDE_DIR}/Core/GlobalVertex.hpp
    ${TimberWolf_INCLUDE_DIR}/Core/Gradient.hpp
    ${TimberWolf_INCLUDE_DIR}/Core/Math.hpp
    ${TimberWolf_INCLUDE_DIR}/Core/Matrix3.hpp
    ${TimberWolf_INCLUDE_DIR}/Core/Matrix3Double.hpp
    ${TimberWolf_INCLUDE_DIR}/Core/Matrix4.hpp
    ${TimberWolf_INCLUDE_DIR}/Core/Matrix4Double.hpp
    ${TimberWolf_INCLUDE_DIR}/Core/Quaternion.hpp
    ${TimberWolf_INCLUDE_DIR}/Core/QuaternionDouble.hpp
    ${TimberWolf_INCLUDE_DIR}/Core/Projection.hpp
    ${TimberWolf_INCLUDE_DIR}/Core/Rotation.hpp
    ${TimberWolf_INCLUDE_DIR}/Core/SpeedGovernor.hpp
    ${TimberWolf_INCLUDE_DIR}/Core/Transformation.hpp
    ${TimberWolf_INCLUDE_DIR}/Core/Vector2.hpp
    ${TimberWolf_INCLUDE_DIR}/Core/Vector2Double.hpp
    ${TimberWolf_INCLUDE_DIR}/Core/Vector3.hpp
    ${TimberWolf_INCLUDE_DIR}/Core/Vector3Double.hpp
    ${TimberWolf_INCLUDE_DIR}/Core/Vertex.hpp

    # Engine Log Subsystem
    ${TimberWolf_INCLUDE_DIR}/Log/ConsoleLogObserver.hpp
    ${TimberWolf_INCLUDE_DIR}/Log/FileLogObserver.hpp
    ${TimberWolf_INCLUDE_DIR}/Log/FunctionLogObserver.hpp
    ${TimberWolf_INCLUDE_DIR}/Log/Log.hpp
    ${TimberWolf_INCLUDE_DIR}/Log/LogObserver.hpp

    # Engine Game Loop Subsystem
    ${TimberWolf_INCLUDE_DIR}/GameLoop/Controller.hpp
    ${TimberWolf_INCLUDE_DIR}/GameLoop/GameLoop.hpp
    ${TimberWolf_INCLUDE_DIR}/GameLoop/GameState.hpp
    ${TimberWolf_INCLUDE_DIR}/GameLoop/GameStateManager.hpp
    ${TimberWolf_INCLUDE_DIR}/GameLoop/GameStateStore.hpp
    ${TimberWolf_INCLUDE_DIR}/GameLoop/Keybinding.hpp
    ${TimberWolf_INCLUDE_DIR}/GameLoop/KeyMod.hpp

    # Engine Graphics Subsystem
    ${TimberWolf_INCLUDE_DIR}/Graphics/Camera.hpp
    ${TimberWolf_INCLUDE_DIR}/Graphics/GraphicsBufferable.hpp
    ${TimberWolf_INCLUDE_DIR}/Graphics/Material.hpp
    ${TimberWolf_INCLUDE_DIR}/Graphics/Mesh.hpp
    ${TimberWolf_INCLUDE_DIR}/Graphics/Model.hpp
    ${TimberWolf_INCLUDE_DIR}/Graphics/Puppet.hpp
    ${TimberWolf_INCLUDE_DIR}/Graphics/Renderer.hpp
    ${TimberWolf_INCLUDE_DIR}/Graphics/Scene.hpp
    ${TimberWolf_INCLUDE_DIR}/Graphics/Texture.hpp
    ${TimberWolf_INCLUDE_DIR}/Graphics/TexturePoint.hpp
    ${TimberWolf_INCLUDE_DIR}/Graphics/VertexSet.hpp

    # Engine OpenGL Graphics Backend
    ${TimberWolf_INCLUDE_DIR}/Graphics/OpenGL/GLComputeShader.hpp
    ${TimberWolf_INCLUDE_DIR}/Graphics/OpenGL/GLFragmentShader.hpp
    ${TimberWolf_INCLUDE_DIR}/Graphics/OpenGL/GLGeometryShader.hpp
    ${TimberWolf_INCLUDE_DIR}/Graphics/OpenGL/GLRenderer.hpp
    ${TimberWolf_INCLUDE_DIR}/Graphics/OpenGL/GLShader.hpp
    ${TimberWolf_INCLUDE_DIR}/Graphics/OpenGL/GLShaderProgram.hpp
    ${TimberWolf_INCLUDE_DIR}/Graphics/OpenGL/GLShaderStore.hpp
    ${TimberWolf_INCLUDE_DIR}/Graphics/OpenGL/GLTesselationControlShader.hpp
    ${TimberWolf_INCLUDE_DIR}/Graphics/OpenGL/GLTesselationEvaluationShader.hpp
    ${TimberWolf_INCLUDE_DIR}/Graphics/OpenGL/GLVertexArray.hpp
    ${TimberWolf_INCLUDE_DIR}/Graphics/OpenGL/GLVertexBuffer.hpp
    ${TimberWolf_INCLUDE_DIR}/Graphics/OpenGL/GLVertexShader.hpp

    # Engine Window Subsystem
    ${TimberWolf_INCLUDE_DIR}/Window/Window.hpp

    # Engine World Subsystem
    ${TimberWolf_INCLUDE_DIR}/World/Entity.hpp
    ${TimberWolf_INCLUDE_DIR}/World/EntityComponent.hpp
    ${TimberWolf_INCLUDE_DIR}/World/PhysicsEntityComponent.hpp
    ${TimberWolf_INCLUDE_DIR}/World/World.hpp

)

# library output
set (LIBRARY_NAME "TimberWolf")
add_library (${LIBRARY_NAME} SHARED ${SOURCES})
set_target_properties (${LIBRARY_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties (${LIBRARY_NAME} PROPERTIES SOVERSION ${TimberWolf_VERSION_MAJOR})
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
    "\${TimberWolf_CMAKE_DIR}/${REL_INCLUDE_DIR}"
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
find_package (Threads REQUIRED)
set (OpenGL_GL_PREFERENCE "GLVND")
find_package (OpenGL REQUIRED)
find_package (GLEW REQUIRED)
find_package (glfw3 REQUIRED)
find_package (glm REQUIRED)
include_directories (${OPENGL_INCLUDE_DIR})
target_link_libraries (${LIBRARY_NAME}
    ${CMAKE_THREAD_LIBS_INIT}
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
    DIRECTORY ${TimberWolf_PUBLIC_HEADER}/ # trailing slash intended, don't remove
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
set (CPACK_RESOURCE_VERSION_MAJOR ${TimberWolf_VERSION_MAJOR})
set (CPACK_RESOURCE_VERSION_MINOR ${TimberWolf_VERSION_MINOR})
set (CPACK_RESOURCE_VERSION_PATCH ${TimberWolf_VERSION_PATCH})
include (CPack)
