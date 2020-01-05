//! state management subsystem

pub mod entity;

use crate::state::entity::Entity;
use std::sync::RwLock;

/// an entire realm of existence, but digital
pub struct World {
    /// a scene graph that encompasses the entire entity, not just the visual portion
    pub graph: Vec<RwLock<WorldGraphNode>>,
}

/// an independent piece of a world, owns descendants that depend on it
#[derive(Default, Debug)]
pub struct WorldGraphNode {
    /// nodes of the scene graph that depend on this one
    pub children: Vec<RwLock<WorldGraphNode>>,
    /// the entity that this node of the scene graph represents
    pub entity: Entity,
}
