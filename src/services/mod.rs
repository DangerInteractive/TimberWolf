//! service locators

use crate::log::Log;

#[derive(Default)]
pub struct ServiceLocator {
    pub log: Log,
}
impl ServiceLocator {
    pub fn new() -> Self {
        Self { log: Log::new() }
    }
}
