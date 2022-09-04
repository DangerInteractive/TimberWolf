//! subsystem for switching between different contexts in the game

use std::mem::swap;
use std::sync::RwLock;

/// something that can be used in a ContextSwitcher
pub trait Context<T> {
    /// pass ownership of a previously active context to the newly active one
    fn take_context(&mut self, _context: T) {
        // do nothing by default
    }
}

/// container for state that is shared among all loop threads
pub struct ContextSwitcher<T: Context<T> + Clone + Send + Sync> {
    /// the context that the game is currently running, or `None` to signify that the game has stopped
    pub active_context: RwLock<Option<Box<T>>>,
}

impl<T: Context<T> + Clone + Send + Sync> ContextSwitcher<T> {
    /// change the context, giving ownership of the previous context to the new one
    pub fn change_context(&self, mut context: Option<Box<T>>) {
        let mut active_context = self
            .active_context
            .write()
            .expect("active_context is poisoned");
        swap(&mut *active_context, &mut context);
        if let Some(ref mut new_context) = *active_context {
            if let Some(old_context) = context {
                new_context.take_context(*old_context);
            }
        }
    }
}

impl<T: Context<T> + Clone + Send + Sync> Default for ContextSwitcher<T> {
    fn default() -> Self {
        Self {
            active_context: RwLock::new(None),
        }
    }
}
