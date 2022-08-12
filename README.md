# TimberWolf
**a high-performance, cross-platform, modern, pure-rust game engine**

## The Core Objectives
TimberWolf is a game engine that strives to be:
1. seamlessly cross-platform (Linux, Windows, MacOS, and possibly more in the future)
2. triply safe (type-safe, memory-safe, and thread-safe)
3. maximally performant
4. extensible and flexible over being easy to use
5. declarative over imperative
6. data-driven
7. mod-maker friendly

## How to Use
This is a Rust library, available through crates.io.
To install in your project, add it to your Cargo.toml as a dependency:
```toml
[dependencies]
timberwolf = "0.5.0"
```
Or run the following command from within your project directory:
```shell
cargo add timberwolf
```

## Running the Demo
As of now, there is only a single demo app, which is intended to demonstrate the
bare minimum subsystems necessary to render a triangle to the screen.

This example can be run by the following commands:
```bash
cd examples/triangle
cargo run
```

## Why should you use this instead of *Some Other Rust Game Engine&trade;*?
For now, you shouldn't.
Many other Rust game engines have large communities, more complete
implementations, more mature codebases, and more developer resources dedicated
to them.
If you want to make a video game right now, those things will be more useful to
you.
If you want to experiment with new game development patterns and ~~learn a bit
about~~ drown in game engine code with me, you're welcome here!

If you're looking for recommendations for more mature game engines to use in the
mean time, then I recommend you check out [Bevy](https://bevyengine.org/).

## What sets this engine apart from its competitors?
For the most part, this engine will naturally have many similarities with many
of the other engines out there.
My original goal in making this engine was as an ambitious learning tool for
myself, but I ultimately would like it to make it to production use.

The end-game for this library has yet to be solidified, but as of right now, I'd
like to differentiate from other engines by putting a stronger focus on using
more declarative/functional programming patterns, whereas gamedev has
traditionally been extremely dependent on imperative and strictly
object-oriented patterns.

I would also like to utilize the advances in WebAssembly in recent years to
build a game engine that treats extension via user-created mods as a first-class
feature.

This is all theoretical until I get the time to put those plans into practice
and find out how they ultimately work out.
For the foreseeable future, that's what this engine will be: experimental.
