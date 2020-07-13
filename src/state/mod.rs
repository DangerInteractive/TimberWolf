//! state management subsystem

use std::hash::Hash;
use std::sync::RwLock;

pub struct State {}
impl State {
    fn query(&self) -> ScopeBuilder {
        unimplemented!()
    }
}

pub struct ScopeBuilder(Scope);
impl ScopeBuilder {
    fn with_component_requirement<T>(self) -> Self {
        self
    }
    fn with_component_option<T>(self) -> Self {
        self
    }
    fn with_component_forbid<T>(self) -> Self {
        self
    }
    fn with_filter(self) -> Self {
        self
    }
}

pub struct Scope {}
