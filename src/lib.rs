//! TimberWolf -  A high-performance 3D focused cross-platform game engine based on Rust

#![deny(dead_code)]
#![deny(missing_docs)]

pub mod context;
pub mod event;
pub mod input;

use crate::context::{Context, ContextSwitcher};

/// represents a game as collection of subsystems
pub struct App<ContextType: Context<ContextType> + Clone + Send + Sync> {
    context_switcher: ContextSwitcher<ContextType>,
}

// TODO: rename this, a monolithic "App" isn't really necessary anymore
impl<ContextType: Context<ContextType> + Clone + Send + Sync> App<ContextType> {
    /// create a new game
    pub fn new() -> Self {
        Default::default()
    }

    // TODO: create some methods for defining threads/loops

    /// run the game!
    pub fn run(&self, context: Box<ContextType>) {
        self.context_switcher.change_context(Some(context));

        // create a channel to gracefully kill all the threads
        // create some MPMC channels to communicate events on
        // spawn some arbitrary threads with rev-limiters and inner-loop code
        // join all the spawned threads
    }
}

impl<ContextType: Context<ContextType> + Clone + Send + Sync> Default for App<ContextType> {
    fn default() -> Self {
        Self {
            context_switcher: Default::default(),
        }
    }
}
