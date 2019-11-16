//! lifecycle and execution subsystem

use crate::services::ServiceLocator;
use winit::Event;

#[derive(PartialEq)]
pub enum Command {
    Continue,
    Stop,
}

pub trait Context: Send + Sync {
    fn render(&self, delta: f64, services: &ServiceLocator) -> Command;
    fn update(&self, delta: f64, services: &ServiceLocator) -> Command;
    fn handle_input(&self, event: Event, services: &ServiceLocator) -> Command;
    fn take_ownership(&self, _context: Option<Box<dyn Context + Send + Sync>>) {}
}
