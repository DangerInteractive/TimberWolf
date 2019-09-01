//! test suite for the timing subsystem

use super::RevLimiter;
use std::time::Duration;

#[test]
fn revlimiter_waits_when_ahead() {
    assert_eq!(
        RevLimiter::calculate_wait(
            Duration::from_millis(1),
            Duration::from_millis(15),
            Duration::from_millis(0)
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
            Duration::from_millis(0)
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
            Duration::from_millis(0)
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
            true
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
            true
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
            true
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
            false
        ),
        Duration::from_millis(0)
    );
}
