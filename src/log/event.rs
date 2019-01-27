//! the log event-handling subsystem

extern crate chrono;
use chrono::{DateTime, Local};
use super::output::console::write_event;

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
    Fatal

}

/// a log message or event, containing a message, date/time, severity level, and context
pub struct Event {

    /// the date and time that the log message was created
    pub time: DateTime<Local>,

    /// the severity level of the log event
    pub severity: Severity,

    /// a name indicating the source or purpose of the log message, used for filtering logs
    pub context: String,

    /// the human-readable message about whatever the log event is trying to say
    pub message: String

}

/// a receiver of log events
pub trait Receiver {

    /// called in order to notify of a log event
    fn notify (event: &Event) where Self: Sized;

}

/// a receiver that displays log messages on the system console (stdout and stderr)
pub struct ConsoleReceiver;
impl Receiver for ConsoleReceiver {

    fn notify (event: &Event) {
        let _ = write_event(&event);
    }

}
