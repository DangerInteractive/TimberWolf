//! TimberWolf -  A high-performance 3D focused cross-platform game engine based on Rust

#![warn(dead_code)]
#![deny(missing_docs)]

pub mod context;
pub mod log;
pub mod timing;

use context::{Context, Story, Request};
use log::{Log, event::{Receiver}};
use std::sync::{Arc};
use std::thread::{sleep, spawn};
use timing::{RevLimiter};

struct GameState {
    pub log: Log,
    pub story: Story
}

/// represents a game as collection of subsystems
pub struct Game {
    state: Arc<GameState>
}

impl Game {

    /// create a new game
    pub fn new () -> Self {
        return Self {
            state: Arc::new(GameState {
                log: Log::new(),
                story: Story::new()
            })
        };
    }

    /// push a context onto the game's story stack
    pub fn push_story_context (&mut self, context: Box<Context + Send + Sync>) {
        self.state.story.push_context(context);
    }

    /// add a receiver to the log subsystem
    pub fn add_log_receiver (&mut self, receiver: Box<Receiver + Send + Sync>) {
        self.state.log.add_receiver(receiver);
    }

    /// run the game!
    pub fn run (&mut self, frames_per_second: u32, ticks_per_second: u32) {

        // start the update loop (on another thread)
        let update_loop_state = self.state.clone();
        let update_loop = spawn(move || {
            let mut rev_limiter = RevLimiter::new_from_frequency(true, true, ticks_per_second, 1.0);
            loop {
                let rev = rev_limiter.next();
                match update_loop_state.story.update(rev.delta_seconds, &update_loop_state.log) {
                    Request::Continue => (),
                    Request::Stop => break,
                }
                sleep(rev.wait);
            }
        });

        // start the render loop (on this thread)
        let mut rev_limiter = RevLimiter::new_from_frequency(false, false, frames_per_second, 1.0);
        loop {
            let rev = rev_limiter.next();
            match self.state.story.render(rev.delta_seconds, &self.state.log) {
                Request::Continue => (),
                Request::Stop => break,
            }
            sleep(rev.wait);
        }

        // make sure the threads don't outlive the game
        let _ = update_loop.join();

    }

}
