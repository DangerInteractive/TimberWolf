//! TimberWolf -  A high-performance 3D focused cross-platform game engine based on Rust

#![warn(dead_code)]
#![deny(missing_docs)]

pub mod color;
pub mod context;
pub mod graphics;
pub mod input;
pub mod log;
pub mod timing;
pub mod window;

use context::{Context, Request, Story};
use log::{event::Receiver, Log};
use std::sync::{Arc, RwLock};
use std::thread::{sleep, spawn};
use timing::RevLimiter;

/// run the inner loop for the current thread
macro_rules! inner_loop {
    ($method: ident, $state: ident, $cycles_per_second: ident) => {
        let mut rev_limiter = RevLimiter::new_from_frequency(false, false, $cycles_per_second, 1.0);
        loop {
            let delta = rev_limiter.begin();
            match $state.story.$method(delta, &$state.log) {
                Request::Continue => (),
                Request::Stop => {
                    match $state.stop_request.write() {
                        Ok(mut stop) => *stop = true,
                        Err(_) => (),
                    }
                    break;
                }
            }
            match $state.stop_request.read() {
                Ok(stop) => {
                    if *stop {
                        break;
                    }
                }
                Err(_) => (),
            }
            let wait = rev_limiter.next();
            sleep(wait);
        }
    };
}

struct GameState {
    pub log: Log,
    pub story: Story,
    pub stop_request: RwLock<bool>,
}

/// represents a game as collection of subsystems
pub struct Game {
    state: Arc<GameState>,
}

impl Game {
    /// create a new game
    pub fn new() -> Self {
        return Self {
            state: Arc::new(GameState {
                log: Log::new(),
                story: Story::new(),
                stop_request: RwLock::new(false),
            }),
        };
    }

    /// push a context onto the game's story stack
    pub fn push_story_context(&mut self, context: Box<Context + Send + Sync>) {
        self.state.story.push_context(context);
    }

    /// add a receiver to the log subsystem
    pub fn add_log_receiver(&mut self, receiver: Box<Receiver + Send + Sync>) {
        self.state.log.add_receiver(receiver);
    }

    /// run the game!
    pub fn run(&mut self, frames_per_second: u32, ticks_per_second: u32) {
        match self.state.stop_request.write() {
            Ok(mut stop) => *stop = false,
            Err(_) => (),
        }

        // start the update loop (on another thread)
        let update_loop_state = self.state.clone();
        let update_loop = spawn(move || {
            inner_loop!(update, update_loop_state, ticks_per_second);
        });

        let render_loop_state = self.state.clone();
        inner_loop!(render, render_loop_state, frames_per_second);

        // make sure the threads don't outlive the game
        let _ = update_loop.join();
    }
}
