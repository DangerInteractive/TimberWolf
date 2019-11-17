//! service locators

use crate::log::Log;

/// a collection of services specific to a game
#[derive(Default)]
pub struct ServiceLocator {
    /// logging service
    pub log: Log,
}
impl ServiceLocator {
    /// create a new service locator (and associated services)
    pub fn new() -> Self {
        Default::default()
    }
}
