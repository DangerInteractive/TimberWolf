# Changelog
All notable changes to this project will be documented in this file

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html)

## Unreleased

## [0.5.0] - 2021-01-09
**The *Sunrise After Ragnarök* Release**

### Added
- `event` namespace, which brings tools for implementing the observer pattern generically

### Changed
- simplified `log::Log::notify`
- rename `GameState` to `GlobalState` and `Game` to `App` to better reflect the multipurpose nature of TimberWolf
- split state management into `wyrd` crate, which will be a real ECS system rather than what I had before
- refactor the timing subsystem to use the observer pattern from `event`
- move `demo` to `examples/triangle`, because there will be more than one demo, and that one will just display a triangle

### Removed
- .idea config files are no longer in-repo (and neither should any other IDE-specific configs going forward)

## [0.4.0] - 2019-11-16
**The *Different Frame of Mind* Release**
> You can lift your head up to the sky   <br />
> Take a deeper breath and give it time  <br />
> You can walk the path among the lines  <br />
> With your shattered frame of mind      <br />
> &ndash; Tristam & Braken, *Frame of Mind*

### Added
- contexts can now handle inbound events from winit windows
- contexts are now responsible for owning and using the contexts they replace
- project rustfmt.toml and .editorconfig files

### Changed
- the `timberwolf::Game` struct now keeps only a single boxed context, allows switching contexts via its shared state struct, and
- the `timberwolf::Game` struct now provides access to services through a `timberwolf::ServiceLocator` struct
- contexts receive `timberwolf::ServiceLocator` and `timberwolf::GameState` references instead of `timberwolf::log::Log` references in their `render` and `update` methods
- contexts are now part of `timberwolf::lifecycle` instead of `timberwolf::context`
- context commands are now `timberwolf::lifecycle::Command` instead of `timberwolf::context::Request`

### Removed
- the `timberwolf::context::Story` struct no longer exists
- contexts no longer have simple `is_*_transparent` methods for determining how previous contexts are handled

## [0.3.2] - 2019-06-17
**The *Don't Stop Me Now* Release**

### Fixed
- Stopping the game loop from one thread would leave the other running


## [0.3.1] - 2019-06-16
**The *Time is Relative* Release**

### Fixed
- Game loop timing not separated into two measurements, causing double execution

### Removed
- the old C++ codebase


## [0.3.0] - 2019-06-15
**The *Rust N00b* Release**

### Added
- Game struct functional
- Context subsystem functional
- Log subsystem functional
- Timing subsystem functional
- Demo app that logs the timing of the render and update loops


## [0.2.0] - 2019-01-27
**The *C++ is dead; long live Rust!* Release**

### Added
- Rust project created

### Deprecated
- C++ codebase deprecated


## [0.1.0] - 2019-01-27
**The *Last Stand of C++* Release**

### Added
- Core game loop.
- Game state subsystem.
- Logging subsystem.
- Input processing subsystem.
- OpenGL rendering subsystem.
- CMake 3.10+ build system.
