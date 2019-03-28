//! the subsystem that governs the timing of the game engine

use std::time::{Duration, Instant};

/// an object that represents a requested condition for the next iteration of a simulation loop
pub struct Rev {

    /// number of seconds that the simulation should elapse during the iteration
    pub delta_seconds: f64,

    /// time to wait before running the next iteration
    pub wait: Duration

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

    /// the last time the loop completed an iteration
    pub last_call: Instant,

    /// the duration of lag incurred behind the real-world elapsed time
    pub lag: Duration,

    /// the ratio of passing time in the loop to passing real time
    pub speed: f64

}

impl RevLimiter {

    /// create a new rev limiter
    pub fn new (
        lockstep_enabled: bool,
        catchup_enabled: bool,
        interval_seconds: f64,
        speed: f64,
    ) -> Self {

        return Self {
            lockstep_enabled,
            catchup_enabled,
            interval: Duration::from_nanos(
                (interval_seconds * 1_000_000_000f64) as u64
            ),
            last_call: Instant::now(),
            lag: Duration::new(0, 0),
            speed
        }

    }

    /// create a new loop from a frequency (iterations per second) instead of an interval
    pub fn new_from_frequency (
        lockstep_enabled: bool,
        catchup_enabled: bool,
        per_second: u32,
        speed: f64
    ) -> Self {

        return Self {
            lockstep_enabled,
            catchup_enabled,
            interval: Duration::from_nanos(
                ((1.0 / (per_second as f64)) * 1_000_000_000.0) as u64
            ),
            last_call: Instant::now(),
            lag: Duration::new(0, 0),
            speed
        };

    }

    /// call the callback, automatically calculating delta time
    pub fn get_delta (&self) -> f64 {
        if self.lockstep_enabled {
            return duration_to_f64(self.interval) * self.speed;
        }
        return duration_to_f64(Instant::now() - self.last_call) * self.speed;
    }

    /// wait until the next iteration can be run
    pub fn get_wait (&self) -> Duration {

        let delta = self.interval - (Instant::now() - self.last_call);

        if delta >= self.interval {
            return Duration::new(0, 0);
        } else {
            if self.lag > delta {
                return Duration::new(0, 0);
            }
            return delta - self.lag;
        }

    }

    /// reset the timer (notify of an iteration)
    pub fn reset_timer (&mut self) {
        self.last_call = Instant::now();
    }

    /// calculate and store the current lag of this loop
    pub fn calc_lag (&mut self) {
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
        self.reset_timer();
        self.calc_lag();
        return rev;
    }

    /// set the interval in seconds
    pub fn set_interval (&mut self, seconds: f64) {
        self.interval = Duration::from_nanos(
            (seconds * 1_000_000_000.0) as u64
        );
    }

    /// set the frequency in iterations per second
    pub fn set_frequency (&mut self, per_second: u32) {
        self.interval = Duration::from_nanos(
            ((1.0 / (per_second as f64)) * 1_000_000_000.0) as u64
        );
    }

}

/// convert a duration to a 64-bit float (seconds)
fn duration_to_f64 (duration: Duration) -> f64 {
    return duration.as_secs() as f64 + (duration.subsec_nanos() as f64 / 1_000_000_000f64);
}
