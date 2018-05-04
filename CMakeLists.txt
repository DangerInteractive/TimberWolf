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
    set (CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
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
set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")
set (CMAKE_CXX_FLAGS_DEBUG "-g -Og")
set (CMAKE_CXX_FLAGS_RELEASE "-O3")
configure_file (
    ${PROJECT_SOURCE_DIR}/include/TimberWolf.hpp.in
    ${PROJECT_SOURCE_DIR}/include/TimberWolf.hpp
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

    # bundled libraries
    ${PROJECT_SOURCE_DIR}/lib/FastNoise/FastNoise.cpp

    # game engine
    ${PROJECT_SOURCE_DIR}/src/Clock.cpp
    ${PROJECT_SOURCE_DIR}/src/Color.cpp
    ${PROJECT_SOURCE_DIR}/src/ComputeShader.cpp
    ${PROJECT_SOURCE_DIR}/src/Console.cpp
    ${PROJECT_SOURCE_DIR}/src/ConsoleLogObserver.cpp
    ${PROJECT_SOURCE_DIR}/src/Controller.cpp
    ${PROJECT_SOURCE_DIR}/src/File.cpp
    ${PROJECT_SOURCE_DIR}/src/FileLogObserver.cpp
    ${PROJECT_SOURCE_DIR}/src/FragmentShader.cpp
    ${PROJECT_SOURCE_DIR}/src/FunctionLogObserver.cpp
    ${PROJECT_SOURCE_DIR}/src/GameLoop.cpp
    ${PROJECT_SOURCE_DIR}/src/GameState.cpp
    ${PROJECT_SOURCE_DIR}/src/GameStateManager.cpp
    ${PROJECT_SOURCE_DIR}/src/GameStateStore.cpp
    ${PROJECT_SOURCE_DIR}/src/GeometryShader.cpp
    ${PROJECT_SOURCE_DIR}/src/Keybinding.cpp
    ${PROJECT_SOURCE_DIR}/src/KeyMod.cpp
    ${PROJECT_SOURCE_DIR}/src/Log.cpp
    ${PROJECT_SOURCE_DIR}/src/LogObserver.cpp
    ${PROJECT_SOURCE_DIR}/src/Model.cpp
    ${PROJECT_SOURCE_DIR}/src/Renderer.cpp
    ${PROJECT_SOURCE_DIR}/src/Scene.cpp
    ${PROJECT_SOURCE_DIR}/src/Shader.cpp
    ${PROJECT_SOURCE_DIR}/src/ShaderProgram.cpp
    ${PROJECT_SOURCE_DIR}/src/ShaderStore.cpp
    ${PROJECT_SOURCE_DIR}/src/SpeedGovernor.cpp
    ${PROJECT_SOURCE_DIR}/src/TesselationControlShader.cpp
    ${PROJECT_SOURCE_DIR}/src/TesselationEvaluationShader.cpp
    ${PROJECT_SOURCE_DIR}/src/ThreadManager.cpp
    ${PROJECT_SOURCE_DIR}/src/VertexArray.cpp
    ${PROJECT_SOURCE_DIR}/src/VertexBuffer.cpp
    ${PROJECT_SOURCE_DIR}/src/VertexShader.cpp
    ${PROJECT_SOURCE_DIR}/src/Window.cpp

)

# list of header files (the public API)
list (APPEND HEADERS

    # config code
    ${PROJECT_SOURCE_DIR}/include/TimberWolf.hpp

    # bundled libraries
    ${PROJECT_SOURCE_DIR}/lib/FastNoise/FastNoise.h

    # game engine
    ${PROJECT_SOURCE_DIR}/include/Clock.hpp
    ${PROJECT_SOURCE_DIR}/include/Color.hpp
    ${PROJECT_SOURCE_DIR}/include/ComputeShader.hpp
    ${PROJECT_SOURCE_DIR}/include/Console.hpp
    ${PROJECT_SOURCE_DIR}/include/ConsoleLogObserver.hpp
    ${PROJECT_SOURCE_DIR}/include/Controller.hpp
    ${PROJECT_SOURCE_DIR}/include/File.hpp
    ${PROJECT_SOURCE_DIR}/include/FileLogObserver.hpp
    ${PROJECT_SOURCE_DIR}/include/FragmentShader.hpp
    ${PROJECT_SOURCE_DIR}/include/FunctionLogObserver.hpp
    ${PROJECT_SOURCE_DIR}/include/GameLoop.hpp
    ${PROJECT_SOURCE_DIR}/include/GameState.hpp
    ${PROJECT_SOURCE_DIR}/include/GameStateManager.hpp
    ${PROJECT_SOURCE_DIR}/include/GameStateStore.hpp
    ${PROJECT_SOURCE_DIR}/include/GeometryShader.hpp
    ${PROJECT_SOURCE_DIR}/include/KeyAction.hpp
    ${PROJECT_SOURCE_DIR}/include/Keybinding.hpp
    ${PROJECT_SOURCE_DIR}/include/KeyMod.hpp
    ${PROJECT_SOURCE_DIR}/include/KeyType.hpp
    ${PROJECT_SOURCE_DIR}/include/Log.hpp
    ${PROJECT_SOURCE_DIR}/include/LogLevel.hpp
    ${PROJECT_SOURCE_DIR}/include/LogObserver.hpp
    ${PROJECT_SOURCE_DIR}/include/Mesh.hpp
    ${PROJECT_SOURCE_DIR}/include/Model.hpp
    ${PROJECT_SOURCE_DIR}/include/Renderer.hpp
    ${PROJECT_SOURCE_DIR}/include/Scene.hpp
    ${PROJECT_SOURCE_DIR}/include/Shader.hpp
    ${PROJECT_SOURCE_DIR}/include/ShaderProgram.hpp
    ${PROJECT_SOURCE_DIR}/include/ShaderStore.hpp
    ${PROJECT_SOURCE_DIR}/include/SpeedGovernor.hpp
    ${PROJECT_SOURCE_DIR}/include/TesselationControlShader.hpp
    ${PROJECT_SOURCE_DIR}/include/TesselationEvaluationShader.hpp
    ${PROJECT_SOURCE_DIR}/include/ThreadManager.hpp
    ${PROJECT_SOURCE_DIR}/include/VertexArray.hpp
    ${PROJECT_SOURCE_DIR}/include/VertexBuffer.hpp
    ${PROJECT_SOURCE_DIR}/include/VertexShader.hpp
    ${PROJECT_SOURCE_DIR}/include/Window.hpp

)

# library output
set (LIBRARY_NAME "TimberWolf")
add_library (${LIBRARY_NAME} SHARED ${SOURCES})
set_target_properties (${LIBRARY_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties (${LIBRARY_NAME} PROPERTIES SOVERSION ${TimberWolf_VERSION_MAJOR})
set_target_properties (${LIBRARY_NAME} PROPERTIES PUBLIC_HEADER "${HEADERS}")
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
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)
configure_file (
    ${PROJECT_SOURCE_DIR}/TimberWolfConfig.cmake.in
    ${PROJECT_BINARY_DIR}/TimberWolfConfig.cmake
    @ONLY
)
set (CONF_INCLUDE_DIRS
    ${REL_INCLUDE_DIR}
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
find_package (OpenGL REQUIRED)
find_package (GLEW REQUIRED)
find_package (glfw3 REQUIRED)
find_package (glm REQUIRED)
include_directories (${OPENGL_INCLUDE_DIR})
target_link_libraries (${LIBRARY_NAME} ${OPENGL_gl_LIBRARY} glfw GLEW glm)

# installation
include (GNUInstallDirs)
install (TARGETS ${LIBRARY_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/TimberWolf
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
