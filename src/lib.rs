//! TimberWolf -  A high-performance 3D focused cross-platform game engine based on Rust

#![warn(dead_code)]
#![warn(missing_docs)]

pub mod color;
pub mod input;
pub mod lifecycle;
pub mod log;
pub mod services;
pub mod timing;

use crate::lifecycle::{Command, Context};
use crate::services::ServiceLocator;
use crate::timing::RevLimiterBuilder;
use std::mem::swap;
use std::sync::{Arc, RwLock};
use std::thread::{sleep, spawn};

pub struct SharedGameState {
    pub services: ServiceLocator,
    pub active_context: RwLock<Option<Box<dyn Context + Send + Sync>>>,
}
impl SharedGameState {
    fn new() -> Self {
        Self {
            services: ServiceLocator::new(),
            active_context: RwLock::new(None),
        }
    }

    /// change the context, giving ownership of the previous context to the new one
    pub fn change_context<'a>(&self, mut context: Option<Box<dyn Context + Send + Sync>>) {
        let mut lock = self
            .active_context
            .write()
            .expect("active_context is poisoned");
        swap(&mut *lock, &mut context);
        if let Some(ref new_context) = *lock {
            new_context.take_ownership(context);
        }
    }
}

/// represents a game as collection of subsystems
pub struct Game {
    shared: Arc<SharedGameState>,
}
impl Game {
    /// create a new game
    pub fn new() -> Self {
        Self {
            shared: Arc::new(SharedGameState::new()),
        }
    }

    pub fn get_shared_state(&self) -> &SharedGameState {
        &self.shared
    }

    /// run the game!
    pub fn run(&self, frames_per_second: u32, ticks_per_second: u32) {
        // start the update loop (on another thread)
        let shared = self.shared.clone();
        let update_loop = spawn(move || {
            let mut rev_limiter = RevLimiterBuilder::new_from_frequency(ticks_per_second as f64)
                .enable_lockstep()
                .enable_catchup()
                .with_speed(1.0)
                .with_lag_secs(0.0)
                .build();
            loop {
                let delta = rev_limiter.begin();
                let mut stop = false;
                {
                    // read lock scope
                    let read_lock = shared
                        .active_context
                        .read()
                        .expect("active_context is poisoned");
                    if let Some(ref context) = *read_lock {
                        if let Command::Stop = context.update(delta, &shared.services) {
                            stop = true;
                        }
                    }
                }
                if stop {
                    // write lock scope
                    shared.change_context(None);
                    break;
                }
                let wait = rev_limiter.next();
                sleep(wait);
            }
        });

        let mut rev_limiter = RevLimiterBuilder::new_from_frequency(frames_per_second as f64)
            .disable_lockstep()
            .disable_catchup()
            .with_speed(1.0)
            .build();
        loop {
            let delta = rev_limiter.begin();
            let mut stop = false;
            {
                // read lock scope
                let read_lock = self
                    .shared
                    .active_context
                    .read()
                    .expect("active_context is poisoned");
                if let Some(ref context) = *read_lock {
                    if let Command::Stop = context.render(delta, &self.shared.services) {
                        stop = true;
                    }
                }
            }
            if stop {
                // write lock scope
                self.shared.change_context(None);
                break;
            }
            let wait = rev_limiter.next();
            sleep(wait);
        }

        // make sure the threads don't outlive the game
        let _ = update_loop.join();
    }
}
