//! the log subsystem

extern crate chrono;
use std::sync::{RwLock};
use chrono::{DateTime, FixedOffset, Local, Utc};
use event::{Event, Receiver, Severity};

pub mod event;
pub mod output;

/// centralized log handler service which receives log messages and dispatches them to receivers
pub struct Log {

    /// receivers to which events will be dispatched
    receivers: RwLock<Vec<RwLock<Box<Receiver + Send + Sync>>>>,

}

impl Log {

    /// create a new log handler service
    pub fn new () -> Log {
        return Log { receivers: RwLock::new(Vec::new()) };
    }

    /// add a receiver to an existing log handler
    pub fn add_receiver (&self, receiver: Box<Receiver + Send + Sync>) {
        match self.receivers.write() {
            Ok (mut receivers) => receivers.push(RwLock::new(receiver)),
            Err (_) => ()
        }
    }

    /// create and notify a log event for the current instant
    pub fn now (&self, severity: Severity, context: &str, message: &str) {
        let event = Event::now(severity, context, message);
        self.notify(&event);
    }

    /// create and notify a log event for a given time in UTC
    pub fn with_utc_time (&self, time: DateTime<Utc>, severity: Severity, context: &str, message: &str) {
        let event = Event::with_utc_time(time, severity, context, message);
        self.notify(&event);
    }

    /// create and notify a log event for a given time in local time
    pub fn with_local_time (&self, time: DateTime<Local>, severity: Severity, context: &str, message: &str) {
        let event = Event::with_local_time(time, severity, context, message);
        self.notify(&event);
    }

    /// create and notify a log event for a given arbitrary time
    pub fn with_time (&self, time: DateTime<FixedOffset>, severity: Severity, context: &str, message: &str) {
        let event = Event::with_time(time, severity, context, message);
        self.notify(&event);
    }

    /// helper function for logging a debug message
    pub fn debug (&self, context: &str, message: &str) {
        self.now(Severity::Debug, context, message);
    }

    /// helper function for logging a verbose message
    pub fn verbose (&self, context: &str, message: &str) {
        self.now(Severity::Verbose, context, message);
    }

    /// helper function for logging an info message
    pub fn info (&self, context: &str, message: &str) {
        self.now(Severity::Info, context, message);
    }

    /// helper function for logging a warning message
    pub fn warning (&self, context: &str, message: &str) {
        self.now(Severity::Warning, context, message);
    }

    /// helper function for logging an error message
    pub fn error (&self, context: &str, message: &str) {
        self.now(Severity::Error, context, message);
    }

    /// helper function for logging a fatal error message
    pub fn fatal (&self, context: &str, message: &str) {
        self.now(Severity::Fatal, context, message);
    }

    /// notify all receivers of a log event
    pub fn notify (&self, event: &Event) {
        match self.receivers.read() {
            Ok (receivers) => {
                for receiver in receivers.iter() {
                    match receiver.write() {
                        Ok(mut receiver) => receiver.notify(event),
                        Err(_) => continue
                    }
                }
            },
            Err (_) => ()
        }
    }

}

impl Receiver for Log {

    /// notify all receivers of a log event
    fn notify (&mut self, event: &Event) {
        Log::notify(self, event);
    }

}
