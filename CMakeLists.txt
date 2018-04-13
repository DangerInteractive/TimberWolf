cmake_minimum_required (VERSION 3.10)

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
set (CMAKE_CXX_FLAGS_DEBUG "-g")
set (CMAKE_CXX_FLAGS_RELEASE "-O3")
configure_file (
    "${PROJECT_SOURCE_DIR}/src/config.hpp.in"
    "${PROJECT_SOURCE_DIR}/src/config.hpp"
)
include_directories ("${PROJECT_BINARY_DIR}")

# list of sources (just for compilation)
list (APPEND SOURCES

    # config code
    ${PROJECT_SOURCE_DIR}/src/config.hpp

    # bundled libraries
    ${PROJECT_SOURCE_DIR}/src/lib/FastNoise/FastNoise.h
    ${PROJECT_SOURCE_DIR}/src/lib/FastNoise/FastNoise.cpp

    # game engine
    ${PROJECT_SOURCE_DIR}/src/class/Clock/Clock.hpp
    ${PROJECT_SOURCE_DIR}/src/class/Clock/Clock.cpp
    ${PROJECT_SOURCE_DIR}/src/class/Color/Color.hpp
    ${PROJECT_SOURCE_DIR}/src/class/Color/Color.cpp
    ${PROJECT_SOURCE_DIR}/src/class/Console/Console.hpp
    ${PROJECT_SOURCE_DIR}/src/class/Console/Console.cpp
    ${PROJECT_SOURCE_DIR}/src/class/ConsoleLogObserver/ConsoleLogObserver.hpp
    ${PROJECT_SOURCE_DIR}/src/class/ConsoleLogObserver/ConsoleLogObserver.cpp
    ${PROJECT_SOURCE_DIR}/src/class/Controller/Controller.hpp
    ${PROJECT_SOURCE_DIR}/src/class/Controller/Controller.cpp
    ${PROJECT_SOURCE_DIR}/src/class/File/File.hpp
    ${PROJECT_SOURCE_DIR}/src/class/File/File.cpp
    ${PROJECT_SOURCE_DIR}/src/class/FileLogObserver/FileLogObserver.hpp
    ${PROJECT_SOURCE_DIR}/src/class/FileLogObserver/FileLogObserver.cpp
    ${PROJECT_SOURCE_DIR}/src/class/FunctionLogObserver/FunctionLogObserver.hpp
    ${PROJECT_SOURCE_DIR}/src/class/FunctionLogObserver/FunctionLogObserver.cpp
    ${PROJECT_SOURCE_DIR}/src/class/GameLoop/GameLoop.hpp
    ${PROJECT_SOURCE_DIR}/src/class/GameLoop/GameLoop.cpp
    ${PROJECT_SOURCE_DIR}/src/class/GameState/GameState.hpp
    ${PROJECT_SOURCE_DIR}/src/class/GameState/GameState.cpp
    ${PROJECT_SOURCE_DIR}/src/class/GameStateManager/GameStateManager.hpp
    ${PROJECT_SOURCE_DIR}/src/class/GameStateManager/GameStateManager.cpp
    ${PROJECT_SOURCE_DIR}/src/class/GameStateStore/GameStateStore.hpp
    ${PROJECT_SOURCE_DIR}/src/class/GameStateStore/GameStateStore.cpp
    ${PROJECT_SOURCE_DIR}/src/class/Keybinding/Keybinding.hpp
    ${PROJECT_SOURCE_DIR}/src/class/Keybinding/Keybinding.cpp
    ${PROJECT_SOURCE_DIR}/src/class/KeyMod/KeyMod.hpp
    ${PROJECT_SOURCE_DIR}/src/class/KeyMod/KeyMod.cpp
    ${PROJECT_SOURCE_DIR}/src/class/Log/Log.hpp
    ${PROJECT_SOURCE_DIR}/src/class/Log/Log.cpp
    ${PROJECT_SOURCE_DIR}/src/class/LogObserver/LogObserver.hpp
    ${PROJECT_SOURCE_DIR}/src/class/LogObserver/LogObserver.cpp
    ${PROJECT_SOURCE_DIR}/src/class/Model/Model.hpp
    ${PROJECT_SOURCE_DIR}/src/class/Model/Model.cpp
    ${PROJECT_SOURCE_DIR}/src/class/Renderer/Renderer.hpp
    ${PROJECT_SOURCE_DIR}/src/class/Renderer/Renderer.cpp
    ${PROJECT_SOURCE_DIR}/src/class/Scene/Scene.hpp
    ${PROJECT_SOURCE_DIR}/src/class/Scene/Scene.cpp
    ${PROJECT_SOURCE_DIR}/src/class/Window/Window.hpp
    ${PROJECT_SOURCE_DIR}/src/class/Window/Window.cpp
    ${PROJECT_SOURCE_DIR}/src/enum/KeyAction/KeyAction.hpp
    ${PROJECT_SOURCE_DIR}/src/enum/KeyType/KeyType.hpp
    ${PROJECT_SOURCE_DIR}/src/enum/LogLevel/LogLevel.hpp

)

# list of header files (the public API)
list (APPEND HEADERS

    # config code
    ${PROJECT_SOURCE_DIR}/src/config.hpp

    # bundled libraries
    ${PROJECT_SOURCE_DIR}/src/lib/FastNoise/FastNoise.h

    # game engine
    ${PROJECT_SOURCE_DIR}/src/class/Clock/Clock.hpp
    ${PROJECT_SOURCE_DIR}/src/class/Color/Color.hpp
    ${PROJECT_SOURCE_DIR}/src/class/Console/Console.hpp
    ${PROJECT_SOURCE_DIR}/src/class/ConsoleLogObserver/ConsoleLogObserver.hpp
    ${PROJECT_SOURCE_DIR}/src/class/Controller/Controller.hpp
    ${PROJECT_SOURCE_DIR}/src/class/File/File.hpp
    ${PROJECT_SOURCE_DIR}/src/class/FileLogObserver/FileLogObserver.hpp
    ${PROJECT_SOURCE_DIR}/src/class/FunctionLogObserver/FunctionLogObserver.hpp
    ${PROJECT_SOURCE_DIR}/src/class/GameLoop/GameLoop.hpp
    ${PROJECT_SOURCE_DIR}/src/class/GameState/GameState.hpp
    ${PROJECT_SOURCE_DIR}/src/class/GameStateManager/GameStateManager.hpp
    ${PROJECT_SOURCE_DIR}/src/class/GameStateStore/GameStateStore.hpp
    ${PROJECT_SOURCE_DIR}/src/class/Keybinding/Keybinding.hpp
    ${PROJECT_SOURCE_DIR}/src/class/KeyMod/KeyMod.hpp
    ${PROJECT_SOURCE_DIR}/src/class/Log/Log.hpp
    ${PROJECT_SOURCE_DIR}/src/class/LogObserver/LogObserver.hpp
    ${PROJECT_SOURCE_DIR}/src/class/Model/Model.hpp
    ${PROJECT_SOURCE_DIR}/src/class/Renderer/Renderer.hpp
    ${PROJECT_SOURCE_DIR}/src/class/Scene/Scene.hpp
    ${PROJECT_SOURCE_DIR}/src/class/Window/Window.hpp
    ${PROJECT_SOURCE_DIR}/src/enum/KeyAction/KeyAction.hpp
    ${PROJECT_SOURCE_DIR}/src/enum/KeyType/KeyType.hpp
    ${PROJECT_SOURCE_DIR}/src/enum/LogLevel/LogLevel.hpp

)

# library output
set (LIBRARY_NAME "TimberWolf")
add_library (${LIBRARY_NAME} SHARED ${SOURCES})
set_target_properties (${LIBRARY_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties (${LIBRARY_NAME} PROPERTIES SOVERSION ${TimberWolf_VERSION_MAJOR})
set_target_properties (${LIBRARY_NAME} PROPERTIES PUBLIC_HEADER ${HEADERS})
configure_file(
    ${PROJECT_SOURCE_DIR}/TimberWolf.pc.in
    ${PROJECT_BINARY_DIR}/TimberWolf.pc
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
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(FILES ${CMAKE_BINARY_DIR}/TimberWolf.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

# packaging
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set (CPACK_RESOURCE_VERSION_MAJOR "${TimberWolf_VERSION_MAJOR}")
set (CPACK_RESOURCE_VERSION_MINOR "${TimberWolf_VERSION_MINOR}")
set (CPACK_RESOURCE_VERSION_PATCH "${TimberWolf_VERSION_PATCH}")
include (CPack)
