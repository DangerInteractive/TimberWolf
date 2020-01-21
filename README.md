# TimberWolf
**a high-performance, cross-platform, modern, pure-rust game engine**

## Objectives
1. seamlessly cross-platform
2. triply safe (type-safe, memory-safe, thread-safe)
3. maximizes performance
4. extensibility and flexibility over ease-of-use
5. declarative over imperative
6. react-ish push-pull reactive APIs

## How to Use
This is a Rust library, available through crates.io. To install as in your
project you simply need to add it to your Cargo.toml as a dependency:
```toml
[dependencies]
timberwolf = "0.5.0"
```

## Running the Demo
As of now, there is only a single demo app, which shows the game loop timing and
logging subsystems.
```bash
cd demo
cargo run
```

## Why should you use this instead of [Amethyst](https://github.com/amethyst/amethyst) or [Piston](https://github.com/PistonDevelopers/piston)?
For now, you shouldn't. Amethyst and Piston both have large communities, more complete
implementations, more mature codebases, and more developer resources dedicated to
them. If you want to make a video game right now, those things will be more useful to
you. If you want to experiment with new game development patterns and ~~learn a bit
about~~ drown in game engine code with me, you're welcome here!

## What sets this engine apart from its competitors?
For the most part, this engine will naturally have many similarities with many of the
other engines out there. My original goal in making this engine was as an ambitious
learning tool for myself, but I ultimately would like it to make it to production use.

The end-game for this library has yet to be solidified, but as of right now, I'd like
to differentiate from other engines by putting a stronger focus on using more
declarative/functional programming patterns, whereas gamedev has traditionally been
extremely dependent on very Imperative Object Oriented patterns. I also want to follow
some of the same decisions that React (the JavaScript library) by designing some API
to use a push-pull reactive API to propagate data between some entities, and across
the boundaries between state and I/O.

This is all theoretical and imaginary until I get the time to put those plans into
practice and find out how they ultimately work out. For the forseeable future, that's
what this engine will be: highly experimental.
