//! the subsystem that governs the timing of the game engine

use std::cell::{Cell};
use std::time::{Duration, Instant};

/// convert a duration to a 64-bit float representing a number of seconds (not multithread-friendly)
pub fn duration_to_seconds (duration: Duration) -> f64 {
    return duration.as_secs() as f64 + (duration.subsec_nanos() as f64 * 1E-9f64);
}

/// convert a floating point number of seconds to a duration (not multithread-friendly)
pub fn seconds_to_duration (seconds: f64) -> Duration {
    return Duration::from_nanos((seconds * 1_000_000_000f64) as u64);
}

/// keeps track of the passing of time from a recorded instant
pub struct Clock {
    reset_time: Cell<Instant>
}

impl Clock {

    /// create a new clock (starting from the moment it's created)
    pub fn new () -> Self {
        return Self { reset_time: Cell::new(Instant::now()) };
    }

    /// reset the clock back to its 0-state (no elapsed time)
    pub fn reset (&mut self) {
        self.reset_time.set(Instant::now());
    }

    /// get the elasped duration
    pub fn elapsed (&self) -> Duration {
        return Instant::now() - self.reset_time.get();
    }

    /// get the number of elapsed seconds as a 64-bit float
    pub fn elapsed_seconds (&self) -> f64 {
        return duration_to_seconds(self.elapsed());
    }

}

/// an object that represents a requested condition for the next iteration of a simulation loop
pub struct Rev {

    /// number of seconds that the simulation should elapse during the iteration
    pub delta_seconds: f64,

    /// time to wait before running the next iteration
    pub wait: Duration,

}

impl Rev {

    /// create a new rev
    pub fn new (delta_seconds: f64, wait: Duration) -> Self {
        return Self { delta_seconds, wait };
    }

}

/// an object that provides a means of controlling the rate at which a loop is run
pub struct RevLimiter {

    /// whether or not each iteration advances by the same interval despite jitter (deterministic loops)
    pub lockstep_enabled: bool,

    /// whether or not the loop should attempt to catch up after incurring lag
    pub catchup_enabled: bool,

    /// the target duration between each iteration of the loop
    pub interval: Duration,

    /// a clock for keeping track of time elapsed since the last iteration
    pub clock: Clock,

    /// the duration of lag incurred behind the real-world elapsed time
    pub lag: Duration,

    /// the ratio of passing time in the loop to passing real time
    pub speed: f64,

}

impl RevLimiter {

    /// create a new rev limiter
    pub fn new (lockstep_enabled: bool, catchup_enabled: bool, interval_seconds: f64, speed: f64) -> Self {
        return Self {
            lockstep_enabled,
            catchup_enabled,
            interval: Duration::from_nanos((interval_seconds * 1_000_000_000f64) as u64),
            clock: Clock::new(),
            lag: Duration::new(0, 0),
            speed,
        };
    }

    /// create a new rev limiter given a custom clock


    /// create a new loop from a frequency (iterations per second) instead of an interval
    pub fn new_from_frequency (lockstep_enabled: bool, catchup_enabled: bool, per_second: u32, speed: f64) -> Self {
        return Self {
            lockstep_enabled,
            catchup_enabled,
            interval: Duration::from_nanos(((1.0 / (per_second as f64)) * 1_000_000_000.0) as u64),
            clock: Clock::new(),
            lag: Duration::new(0, 0),
            speed,
        };
    }

    /// call the callback, automatically calculating delta time
    fn get_delta (&self) -> f64 {
        if self.lockstep_enabled {
            return duration_to_seconds(self.interval) * self.speed;
        }
        return self.clock.elapsed_seconds() * self.speed;
    }

    /// wait until the next iteration can be run
    fn get_wait (&self) -> Duration {

        let elapsed = self.clock.elapsed();
        if elapsed >= self.interval {
            return Duration::new(0, 0);
        } else {
            let delta = self.interval - elapsed;
            if self.lag > delta {
                return Duration::new(0, 0);
            } else {
                return delta - self.lag;
            }
        }

    }

    /// calculate and store the current lag of this loop
    fn calc_lag (&mut self) {
        if self.catchup_enabled {
            let wait = self.get_wait();
            if wait > Duration::new(0, 0) {
                self.lag = Duration::new(0, 0);
            } else {
                if self.lag > self.interval {
                    self.lag -= self.interval;
                } else {
                    self.lag = Duration::new(0, 0);
                }
            }
        }
    }

    /// execute the next iteration of the loop, waiting if necessary (this is the heart of the loop)
    pub fn next (&mut self) -> Rev {
        let rev = Rev::new(self.get_delta(), self.get_wait());
        self.clock.reset();
        self.calc_lag();
        return rev;
    }

    /// set the interval in seconds
    pub fn set_interval (&mut self, seconds: f64) {
        self.interval = Duration::from_nanos((seconds * 1_000_000_000.0) as u64);
    }

    /// set the frequency in iterations per second
    pub fn set_frequency (&mut self, per_second: u32) {
        self.interval = Duration::from_nanos(((1.0 / (per_second as f64)) * 1_000_000_000.0) as u64);
    }

}
