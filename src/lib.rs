#![warn(dead_code)]
#![deny(missing_docs)]

//! TimberWolf -  A high-performance 3D focused cross-platform game engine based on Rust

pub mod context;
pub mod log;
pub mod turbine;

#[cfg(test)]
mod test;

/// represents a game as collection of subsystems
pub struct Game {

    /// the name of the game
    pub name: String,

    /// the log handler service
    pub log: log::Log

}

impl Game {

    /// create a new game
    pub fn new (name: String) -> Self {
        return Game {
            name: name,
            log: log::Log::new()
        };
    }

}
