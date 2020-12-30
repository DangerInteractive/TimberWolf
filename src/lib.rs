//! TimberWolf -  A high-performance 3D focused cross-platform game engine based on Rust

#![deny(dead_code)]
#![deny(missing_docs)]

pub mod color;
pub mod event;
pub mod input;
pub mod lifecycle;
pub mod log;
pub mod memory;
pub mod state;

use crate::event::timing::RevLimiterBuilder;
use crate::lifecycle::{Command, Context};
use crate::log::Log;
use std::mem::swap;
use std::sync::{Arc, RwLock};
use std::thread::{sleep, spawn};

/// container for state that is shared among all loop threads
#[derive(Default)]
pub struct GlobalState {
    /// the context that the game is currently running, or `None` to signify that the game has stopped
    pub active_context: RwLock<Option<Box<dyn Context + Send + Sync>>>,
}
impl GlobalState {
    /// change the context, giving ownership of the previous context to the new one
    pub fn change_context(&self, mut context: Option<Box<dyn Context + Send + Sync>>) {
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

/// a collection of services specific to a game
#[derive(Default)]
pub struct ServiceLocator {
    /// logging service
    pub log: Log,
}
impl ServiceLocator {
    /// create a new service locator (and associated services)
    pub fn new() -> Self {
        Default::default()
    }
}

/// represents a game as collection of subsystems
#[derive(Default)]
pub struct App {
    /// service locator for accessing common game service
    pub services: Arc<ServiceLocator>,
    state: Arc<GlobalState>,
}
impl App {
    /// create a new game
    pub fn new() -> Self {
        Default::default()
    }

    /// get access to the game's state object
    pub fn get_state(&self) -> &GlobalState {
        &self.state
    }

    /// get access to the game's service locator
    pub fn get_services(&self) -> &ServiceLocator {
        &self.services
    }

    /// run the game!
    pub fn run(
        &self,
        context: Box<dyn Context + Send + Sync>,
        frames_per_second: u32,
        ticks_per_second: u32,
    ) {
        self.state.change_context(None);
        self.state.change_context(Some(context));

        // start the update loop (on another thread)
        let services = self.services.clone();
        let state = self.state.clone();
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
                    let read_lock = state
                        .active_context
                        .read()
                        .expect("active_context is poisoned");
                    if let Some(ref context) = *read_lock {
                        if let Command::Stop = context.update(delta, &services, &state) {
                            stop = true;
                        }
                    }
                }
                if stop {
                    // write lock scope
                    state.change_context(None);
                    break;
                }
                let wait = rev_limiter.end();
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
                    .state
                    .active_context
                    .read()
                    .expect("active_context is poisoned");
                if let Some(ref context) = *read_lock {
                    if let Command::Stop = context.render(delta, &self.services) {
                        stop = true;
                    }
                }
            }
            if stop {
                // write lock scope
                self.state.change_context(None);
                break;
            }
            let wait = rev_limiter.end();
            sleep(wait);
        }

        // make sure the threads don't outlive the game
        let _ = update_loop.join();
    }
}
