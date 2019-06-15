//! the log event-handling subsystem

extern crate chrono;
use super::output::console::write_event;
use chrono::{DateTime, FixedOffset, Local, Utc};

/// the severity level of a log event
pub enum Severity {

    /// to be used by developers during development, shouldn't exist in production code
    Debug,

    /// generally unimportant and not of interest to most users
    Verbose,

    /// low importance and doesn't likely indicate a problem
    Info,

    /// high importance, potential problem or unexpected behavior
    Warning,

    /// high importance, something definitely went wrong
    Error,

    /// something went wrong, and the program will fail
    Fatal,

}

/// a log message or event, containing a message, date/time, severity level, and context
pub struct Event {

    /// the date and time that the log message was created
    pub time: DateTime<Utc>,

    /// the severity level of the log event
    pub severity: Severity,

    /// a name indicating the source or purpose of the log message, used for filtering logs
    pub context: String,

    /// the human-readable message about whatever the log event is trying to say
    pub message: String,

}

impl Event {

    /// create a new event marked with the current time
    pub fn now (severity: Severity, context: &str, message: &str) -> Self {
        return Event {
            time: Utc::now(),
            severity,
            context: context.to_owned(),
            message: message.to_owned(),
        };
    }

    /// create a new event marked with a given UTC date and time
    pub fn with_utc_time (time: DateTime<Utc>, severity: Severity, context: &str, message: &str) -> Self {
        return Event {
            time,
            severity,
            context: context.to_owned(),
            message: message.to_owned(),
        };
    }

    /// create a new event marked with a given local date and time
    pub fn with_local_time (time: DateTime<Local>, severity: Severity, context: &str, message: &str) -> Self {
        return Event {
            time: time.with_timezone(&Utc),
            severity,
            context: context.to_owned(),
            message: message.to_owned(),
        };
    }

    /// create a new event marked with a given fixed offset date and time
    pub fn with_time (time: DateTime<FixedOffset>, severity: Severity, context: &str, message: &str) -> Self {
        return Event {
            time: time.with_timezone(&Utc),
            severity,
            context: context.to_owned(),
            message: message.to_owned(),
        };
    }

}

/// a receiver of log events
pub trait Receiver {

    /// called in order to notify of a log event
    fn notify (&mut self, event: &Event);

}

/// a receiver that displays log messages on the system console (stdout and stderr)
pub struct ConsoleReceiver;
impl ConsoleReceiver {

    /// create a new console log receiver
    pub fn new () -> Self {
        return Self;
    }

}
impl Receiver for ConsoleReceiver {

    fn notify (&mut self, event: &Event) {
        let _ = write_event(&event);
    }

}
