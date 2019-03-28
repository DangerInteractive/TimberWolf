//! TimberWolf -  A high-performance 3D focused cross-platform game engine based on Rust

#![warn(dead_code)]
#![deny(missing_docs)]

pub mod context;
pub mod log;
pub mod timing;

#[cfg(test)]
mod test;

use std::sync::{Arc, Mutex};
use std::thread::{spawn, sleep};
use context::{Story};
use timing::{RevLimiter};

/// represents a game as collection of subsystems
pub struct Game {
    story: Arc<Mutex<Story>>
}

impl Game {

    /// create a new game
    pub fn new () -> Self {
        let game = Self {
            story: Arc::new(Mutex::new(Story::new()))
        };
        return game;
    }

    /// run the game!
    pub fn run (&mut self, frames_per_second: u32, ticks_per_second: u32) {

        // start the update loop (on another thread)
        let update_loop_story = self.story.clone();
        let update_loop = spawn(move || {
            let mut rev_limiter = RevLimiter::new_from_frequency(true, true, ticks_per_second, 1.0);
            loop {
                let rev = rev_limiter.next();
                let end;
                {
                    let story = update_loop_story.lock();
                    end = match story {
                        Ok(mut locked_story) => {
                            locked_story.update(rev.delta_seconds)
                        }
                        Err(_) => {
                            true
                        }
                    }
                }
                if end {
                    break;
                }
                sleep(rev.wait);
            }
        });

        // start the render loop (on this thread)
        let mut rev_limiter = RevLimiter::new_from_frequency(false, false, frames_per_second, 1.0);
        loop {
            let rev = rev_limiter.next();
            let end;
            {
                let story = self.story.lock();
                end = match story {
                    Ok(mut locked_story) => {
                        locked_story.render(rev.delta_seconds)
                    }
                    Err(_) => {
                        true
                    }
                }
            }
            if end {
                break;
            }
            sleep(rev.wait);
        }

        // make sure the threads don't outlive the game
        let _ = update_loop.join();

    }

}
