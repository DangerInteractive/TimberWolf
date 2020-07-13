//! lifecycle and execution subsystem

use crate::GameState;
use crate::ServiceLocator;
use winit::Event;

/// a command that tells one of the game loops what to do before the next iteration.
#[derive(PartialEq)]
pub enum Command {
    /// signal to keep running the loop(s)
    Continue,
    /// signal to stop the loop(s)
    Stop,
}

/// An object that represents a set of subroutines defining how to run the game. It may encapsulate
/// game state, and it is optionally given ownership of the previous context after a context switch.
pub trait Context: Send + Sync {
    /// function that renders the game
    fn render(&self, delta: f64, services: &ServiceLocator) -> Command;
    /// function that updates game state
    fn update(&self, delta: f64, services: &ServiceLocator, state: &GlobalState) -> Command;
    /// function that handles inbound window/device events
    fn handle_input(&self, event: Event, services: &ServiceLocator, state: &GlobalState) -> Command;
    /// a function that is called after a context switch, passing ownership of the previous context
    /// into this context (can be used to override the previous context's functionality by proxying)
    fn take_ownership(&self, _context: Option<Box<dyn Context + Send + Sync>>) {}
}
