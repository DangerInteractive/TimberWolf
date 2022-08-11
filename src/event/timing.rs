//! event emitters based on timing

use std::cell::Cell;
use std::time::{Duration, Instant};

/// keeps track of the passing of time from a recorded instant
pub struct Clock {
    reset_time: Cell<Instant>,
}

impl Clock {
    /// create a new clock (starting from the moment it's created)
    pub fn new() -> Self {
        Default::default()
    }

    /// reset the clock back to its default state (no elapsed time)
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

impl Default for Clock {
    fn default() -> Self {
        Self {
            reset_time: Cell::new(Instant::now()),
        }
    }
}

/// an object that provides a means of controlling the rate at which a loop is run
pub struct RevLimiter {
    /// whether or not each iteration advances by the same interval despite jitter (deterministic loops)
    pub fixed_time_stepping_enabled: bool,
    /// whether or not the loop should attempt to catch up after incurring lag
    pub lag_catch_up_enabled: bool,
    /// the target duration between each iteration of the loop
    pub interval: Duration,
}

impl RevLimiter {
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
    fn get_wait(&self, elapsed: Duration, lag: Duration) -> Duration {
        Self::calculate_wait(elapsed, self.interval, lag)
    }

    /// calculate the remaining lag after a loop iteration
    fn calculate_lag(
        last_wait: Duration,
        target_interval: Duration,
        accumulated_lag: Duration,
        catchup_enabled: bool,
    ) -> Duration {
        if catchup_enabled {
            if last_wait >= target_interval {
                let lost_time = last_wait - target_interval;
                accumulated_lag + lost_time
            } else {
                let gained_time = target_interval - last_wait;
                if accumulated_lag > gained_time {
                    accumulated_lag - gained_time
                } else {
                    Duration::new(0, 0)
                }
            }
        } else {
            Duration::new(0, 0)
        }
    }

    /// signal that execution for this iteration of the loop has completed, and prepare for the next iteration
    pub fn end(&mut self, clock: &Clock, lag: Duration) -> (Duration, Duration) {
        let wait = self.get_wait(clock.elapsed(), lag);
        (
            Self::calculate_lag(wait, self.interval, lag, self.lag_catch_up_enabled),
            wait,
        )
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
                fixed_time_stepping_enabled: false,
                lag_catch_up_enabled: false,
                interval: Duration::from_secs_f64(interval_secs),
            },
        }
    }

    /// begin building a RevLimiter based off of a frequency (iterations per second)
    pub fn new_from_frequency(cycles_per_sec: f64) -> Self {
        Self {
            wrapped: RevLimiter {
                fixed_time_stepping_enabled: false,
                lag_catch_up_enabled: false,
                interval: Duration::from_secs_f64(1.0 / cycles_per_sec),
            },
        }
    }

    /// enable lockstep functionality: each iteration advances by the same interval despite jitter (deterministic loops)
    pub fn enable_lockstep(mut self) -> Self {
        self.wrapped.fixed_time_stepping_enabled = true;
        self
    }

    /// disable lockstep functionality: each iteration may advance by a different amount of time depending on conditions (non-deterministic loops)
    pub fn disable_lockstep(mut self) -> Self {
        self.wrapped.fixed_time_stepping_enabled = false;
        self
    }

    /// enable catchup functionality: the loop attempts to catch up after incurring lag
    pub fn enable_catchup(mut self) -> Self {
        self.wrapped.lag_catch_up_enabled = true;
        self
    }

    /// disable catchup functionality: the loop does not attempt to catch up after incurring lag
    pub fn disable_catchup(mut self) -> Self {
        self.wrapped.lag_catch_up_enabled = false;
        self
    }

    /// build the RevLimiter, disposing of the builder and returning the RevLimiter struct
    pub fn build(self) -> RevLimiter {
        self.wrapped
    }
}

#[test]
fn revlimiter_waits_when_ahead() {
    assert_eq!(
        RevLimiter::calculate_wait(
            Duration::from_millis(1),
            Duration::from_millis(15),
            Duration::from_millis(0),
        ),
        Duration::from_millis(14)
    );
}

#[test]
fn revlimiter_continues_when_on_time() {
    assert_eq!(
        RevLimiter::calculate_wait(
            Duration::from_millis(15),
            Duration::from_millis(15),
            Duration::from_millis(0),
        ),
        Duration::from_millis(0)
    );
}

#[test]
fn revlimiter_continues_when_behind() {
    assert_eq!(
        RevLimiter::calculate_wait(
            Duration::from_millis(19),
            Duration::from_millis(15),
            Duration::from_millis(0),
        ),
        Duration::from_millis(0)
    );
}

#[test]
fn revlimiter_decreases_lag_when_ahead() {
    assert_eq!(
        RevLimiter::calculate_lag(
            Duration::from_millis(1),
            Duration::from_millis(15),
            Duration::from_millis(100),
            true,
        ),
        Duration::from_millis(86)
    );
}

#[test]
fn revlimiter_keeps_lag_when_on_time() {
    assert_eq!(
        RevLimiter::calculate_lag(
            Duration::from_millis(15),
            Duration::from_millis(15),
            Duration::from_millis(100),
            true,
        ),
        Duration::from_millis(100)
    );
}

#[test]
fn revlimiter_increases_lag_when_behind() {
    assert_eq!(
        RevLimiter::calculate_lag(
            Duration::from_millis(27),
            Duration::from_millis(15),
            Duration::from_millis(100),
            true,
        ),
        Duration::from_millis(112)
    );
}

#[test]
fn revlimiter_has_no_lag_without_catchup() {
    assert_eq!(
        RevLimiter::calculate_lag(
            Duration::from_millis(27),
            Duration::from_millis(15),
            Duration::from_millis(100),
            false,
        ),
        Duration::from_millis(0)
    );
}
