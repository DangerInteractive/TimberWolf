//! the subsystem that runs the hot and fast inner loops of the game engine

use std::time::{Duration, Instant};
use std::thread::sleep;

/// the action which is repeatedly executed inside of a turbine loop
pub trait Rotor {

    /// execute a single iteration of the action, and return whether or not the loop should continue
    fn spin (&mut self, delta_seconds: f64) -> bool;

}

/// an object that provides a means of controlling the rate at which a loop is run
pub struct Throttle {

    /// whether or not each iteration advances by the same interval despite jitter (deterministic loops)
    lockstep_enabled: bool,

    /// whether or not the loop should attempt to catch up after incurring lag
    catchup_enabled: bool,

    /// the target duration between each iteration of the loop
    interval: Duration,

    /// the last time the loop completed an iteration
    last_call: Instant,

    /// the duration of lag incurred behind the real-world elapsed time
    lag: Duration,

    /// the ratio of passing time in the loop to passing real time
    speed: f64

}

impl Throttle {

    /// create a new loop
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
    pub fn next (&mut self) -> (f64, Duration) {
        let rev = (self.get_delta(), self.get_wait());
        self.reset_timer();
        self.calc_lag();
        return rev;
    }

}

/// an object that handles the looping of loops
pub struct Turbine {

    /// the object that controls the speed of the loop
    throttle: Throttle,

    /// the object that determines what the loop does
    rotor: Box<Rotor>,

}

impl Turbine {

    /// create a new turbine given a throttle and a rotor
    pub fn new <T: 'static + Rotor> (throttle: Throttle, rotor: T) -> Self {
        return Self {
            throttle,
            rotor: Box::new(rotor)
        };
    }

    /// run the turbine
    pub fn run (&mut self) {
        loop {
            let (delta, wait) = self.throttle.next();
            sleep(wait);
            if !self.rotor.spin(delta) {
                break; // returning false kills the loop
            }
        }
    }

}

/// convert a duration to a 64-bit float (seconds)
fn duration_to_f64 (duration: Duration) -> f64 {
    return duration.as_secs() as f64 + (duration.subsec_nanos() as f64 / 1_000_000_000f64);
}
