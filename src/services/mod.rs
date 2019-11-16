//! service locators

use crate::log::Log;

pub struct ServiceLocator {
    pub log: Log,
}
impl ServiceLocator {
    pub fn new() -> Self {
        Self { log: Log::new() }
    }
}
