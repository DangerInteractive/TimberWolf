//! the subsystem that handles the scheduling and completion of tasks

use std::time::{Duration, Instant};
use std::thread::{sleep};

/// an object that provides a means of controlling the rate at which a loop is run
pub struct Loop<T> where T: FnMut(Duration) {

    /// callback function that gets looped, receiving the delta time
    callback: T,

    /// whether or not each iteration advances by the same interval despite jitter (deterministic loops)
    lockstep_enabled: bool,

    /// whether or not the loop should attempt to catch up after incurring lag
    catchup_enabled: bool,

    /// the target duration between each iteration of the loop
    interval: Duration,

    /// the last time the loop completed an iteration
    last_call: Instant,

    /// the duration of lag incurred behind the real-world elapsed time
    lag: Duration

}

impl<T> Loop<T> where T: FnMut(Duration) {

    /// create a new loop
    pub fn new (
        callback: T,
        lockstep_enabled: bool,
        catchup_enabled: bool,
        interval_seconds: f64
    ) -> Self {

        return Loop {
            callback,
            lockstep_enabled,
            catchup_enabled,
            interval: Duration::from_nanos(
                (interval_seconds * 1_000_000_000.0) as u64
            ),
            last_call: Instant::now(),
            lag: Duration::new(0, 0)
        }

    }

    /// create a new loop from a frequency (iterations per second) instead of an interval
    pub fn new_from_frequency (
        callback: T,
        lockstep_enabled: bool,
        catchup_enabled: bool,
        per_second: u32,
    ) -> Self {

        return Loop {
            callback,
            lockstep_enabled,
            catchup_enabled,
            interval: Duration::from_nanos(
                ((1.0 / (per_second as f64)) * 1_000_000_000.0) as u64
            ),
            last_call: Instant::now(),
            lag: Duration::new(0, 0)
        };

    }

    /// call the callback manually
    pub fn call (&mut self, delta: Duration) {
        (self.callback)(delta);
        self.last_call = Instant::now();
    }

    /// call the callback, automatically calculating delta time
    pub fn call_now (&mut self) {
        if self.lockstep_enabled {
            self.call(self.interval);
        } else {
            self.call(Instant::now() - self.last_call);
        }
    }

    /// wait until the next iteration can be run
    pub fn wait (&mut self) {
        if self.catchup_enabled {
            let available = self.interval - (Instant::now() - self.last_call);
            let lag = self.lag - available;
            if lag <= Duration::new(0, 0) {
                sleep(Duration::new(0, 0) - lag); // leftover time after paying off lag
                self.lag = Duration::new(0, 0); // caught up
            } else {
                self.lag = lag; // record remaining lag for next iteration
            }
        } else {
            sleep(self.interval - (Instant::now() - self.last_call));
        }
    }

    /// execute the next iteration of the loop, waiting if necessary (this is the heart of the loop)
    pub fn next (&mut self) {
        self.wait();
        self.call_now();
    }

}
