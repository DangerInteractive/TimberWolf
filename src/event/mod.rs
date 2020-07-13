//! the subsystem that governs the timing of the game engine

use std::cell::Cell;
use std::time::{Duration, Instant};

#[cfg(test)]
mod test;

/// keeps track of the passing of time from a recorded instant
pub struct Clock {
    reset_time: Cell<Instant>,
}
impl Default for Clock {
    fn default() -> Self {
        Self {
            reset_time: Cell::new(Instant::now()),
        }
    }
}
impl Clock {
    /// create a new clock (starting from the moment it's created)
    pub fn new() -> Self {
        Default::default()
    }

    /// reset the clock back to its 0-state (no elapsed time)
    pub fn reset(&self) {
        self.reset_time.set(Instant::now());
    }

    /// get the elapsed duration
    pub fn elapsed(&self) -> Duration {
        Instant::now() - self.reset_time.get()
    }

    /// get the number of elapsed seconds as a 64-bit float
    pub fn elapsed_seconds(&self) -> f64 {
        self.elapsed().as_secs_f64()
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
    /// call the callback, automatically calculating delta time
    fn get_delta(&self, current_elapsed: Duration) -> f64 {
        if self.lockstep_enabled {
            return self.interval.as_secs_f64() * self.speed;
        }
        current_elapsed.as_secs_f64() * self.speed
    }

    /// calculate a sleep duration after a loop iteration
    fn calculate_wait(
        current_elapsed: Duration,
        target_interval: Duration,
        current_lag: Duration,
    ) -> Duration {
        if current_elapsed >= target_interval {
            Duration::new(0, 0)
        } else {
            let delta = target_interval - current_elapsed;
            if current_lag > delta {
                Duration::new(0, 0)
            } else {
                delta - current_lag
            }
        }
    }

    /// get the time to wait until the next loop iteration should run
    fn get_wait(&self, current_elapsed: Duration) -> Duration {
        Self::calculate_wait(current_elapsed, self.interval, self.lag)
    }

    /// calculate the remaining lag after a loop iteration
    fn calculate_lag(
        last_wait: Duration,
        target_interval: Duration,
        current_lag: Duration,
        catchup_enabled: bool,
    ) -> Duration {
        if catchup_enabled {
            if last_wait >= target_interval {
                let lost_time = last_wait - target_interval;
                current_lag + lost_time
            } else {
                let gained_time = target_interval - last_wait;
                if current_lag > gained_time {
                    current_lag - gained_time
                } else {
                    Duration::new(0, 0)
                }
            }
        } else {
            Duration::new(0, 0)
        }
    }

    /// calculate and store the current lag of this loop
    fn update_lag(&mut self, current_wait: Duration) {
        self.lag = Self::calculate_lag(current_wait, self.interval, self.lag, self.catchup_enabled);
    }

    /// signal that execution for this iteration of the loop has started, mainly for the purpose of starting a timer
    pub fn begin(&mut self) -> f64 {
        let delta = self.get_delta(self.clock.elapsed());
        self.clock.reset();
        delta
    }

    /// signal that execution for this iteration of the loop has completed, and prepare for the next iteration
    pub fn end(&mut self) -> Duration {
        let wait = self.get_wait(self.clock.elapsed());
        self.clock.reset();
        self.update_lag(wait);
        wait
    }

    /// set the interval in seconds
    pub fn set_interval(&mut self, seconds: f64) {
        self.interval = Duration::from_nanos((seconds * 1_000_000_000.0) as u64);
    }

    /// set the frequency in iterations per second
    pub fn set_frequency(&mut self, per_second: u32) {
        self.interval =
            Duration::from_nanos(((1.0 / (per_second as f64)) * 1_000_000_000.0) as u64);
    }
}

/// builder for constructing a RevLimiter struct with a fluent API
pub struct RevLimiterBuilder {
    wrapped: RevLimiter,
}
impl RevLimiterBuilder {
    /// begin building a RevLimiter based off of an interval (time between iterations) in seconds
    pub fn new_from_interval_secs(interval_secs: f64) -> Self {
        Self {
            wrapped: RevLimiter {
                lockstep_enabled: false,
                catchup_enabled: false,
                interval: Duration::from_secs_f64(interval_secs),
                clock: Clock::new(),
                lag: Duration::new(0, 0),
                speed: 1.0,
            },
        }
    }

    /// begin building a RevLimiter based off of a frequency (iterations per second)
    pub fn new_from_frequency(cycles_per_sec: f64) -> Self {
        Self {
            wrapped: RevLimiter {
                lockstep_enabled: false,
                catchup_enabled: false,
                interval: Duration::from_secs_f64(1.0 / cycles_per_sec),
                clock: Clock::new(),
                lag: Duration::new(0, 0),
                speed: 1.0,
            },
        }
    }

    /// enable lockstep functionality: each iteration advances by the same interval despite jitter (deterministic loops)
    pub fn enable_lockstep(mut self) -> Self {
        self.wrapped.lockstep_enabled = true;
        self
    }

    /// disable lockstep functionality: each iteration may advance by a different amount of time depending on conditions (non-deterministic loops)
    pub fn disable_lockstep(mut self) -> Self {
        self.wrapped.lockstep_enabled = false;
        self
    }

    /// enable catchup functionality: the loop attempts to catch up after incurring lag
    pub fn enable_catchup(mut self) -> Self {
        self.wrapped.catchup_enabled = true;
        self
    }

    /// disable catchup functionality: the loop does not attempt to catch up after incurring lag
    pub fn disable_catchup(mut self) -> Self {
        self.wrapped.catchup_enabled = false;
        self
    }

    /// set the initial lag in seconds
    pub fn with_lag_secs(mut self, secs: f64) -> Self {
        self.wrapped.lag = Duration::from_secs_f64(secs);
        self
    }

    /// set the relative speed of time in the loop, where 1.0 is real-time
    pub fn with_speed(mut self, speed: f64) -> Self {
        self.wrapped.speed = speed;
        self
    }

    /// build the RevLimiter, disposing of the builder and returning the RevLimiter struct
    pub fn build(self) -> RevLimiter {
        self.wrapped
    }
}
