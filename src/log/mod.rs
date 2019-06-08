//! the log subsystem

pub mod event;
pub mod output;

/// centralized log handler service which receives log messages and dispatches them to receivers
pub struct Log {

    /// receivers to which events will be dispatched
    receivers: Vec<Box<event::Receiver + Send + Sync>>,

}

impl Log {

    /// create a new log handler service
    pub fn new () -> Log {
        return Log { receivers: Vec::new() };
    }

    /// add a receiver to an existing log handler
    pub fn add_receiver (&mut self, receiver: Box<event::Receiver + Send + Sync>) {
        self.receivers.push(receiver);
    }

}
