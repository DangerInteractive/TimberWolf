# Changelog
All notable changes to this project will be documented in this file

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html)


## [0.1.0] - 2019-01-27

### Added
- Core game loop.
- Game state subsystem.
- Logging subsystem.
- Input processing subsystem.
- OpenGL rendering subsystem.
- CMake 3.10+ build system.

### Notes
- Final C++ release, engine is switching to Rust


## [0.2.0] - 2019-01-27

### Added
- Rust project created

### Changes
- C++ codebase deprecated


## [0.3.0] - 2019-06-15

### Added
- Game struct functional
- Context subsystem functional
- Log subsystem functional
- Timing subsystem functional
- Demo app that logs the timing of the render and update loops


## [0.3.1] - 2019-06-16

### Fixed
- Game loop timing not separated into two measurements, causing double execution

## [0.3.2] - 2019-06-17

### Fixed
- Stopping the game loop from one thread would leave the other running
