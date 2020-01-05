//! entity subsystem

use crate::{GameState, ServiceLocator};
use cgmath::{Quaternion, Vector3};
use std::fmt::Debug;
use std::sync::RwLock;
use winit::Event;

/// an object in the world, and the components that define how it functions
#[derive(Debug)]
pub struct Entity {
    /// components determining what the entity does and how it works
    pub components: Vec<RwLock<Box<dyn EntityComponent>>>,
    /// the position of the entity in a three-dimensional space
    pub translation: RwLock<Vector3<f64>>,
    /// the rotation of the entity
    pub rotation: RwLock<Quaternion<f32>>,
    /// the scale of the entity (independent for each of the three axes)
    pub scale: RwLock<Vector3<f32>>,
}
impl Entity {
    /// process a render tick
    pub fn render(&self, entity: &Entity, delta: f64, services: &ServiceLocator) {
        for component in self.components.iter() {
            component
                .read()
                .expect("components is poisoned")
                .render(entity, delta, services);
        }
    }
    /// process an update tick
    pub fn update(
        &mut self,
        entity: &mut Entity,
        delta: f64,
        services: &ServiceLocator,
        game_state: &GameState,
    ) {
        for component in self.components.iter() {
            component
                .write()
                .expect("components is poisoned")
                .update(entity, delta, services, game_state);
        }
    }
    /// process an input event
    pub fn handle_input(
        &mut self,
        entity: &mut Entity,
        event: &Event,
        services: &ServiceLocator,
        game_state: &GameState,
    ) {
        for component in self.components.iter() {
            component
                .write()
                .expect("components is poisoned")
                .handle_input(entity, event, services, game_state);
        }
    }
}
impl Default for Entity {
    fn default() -> Self {
        Self {
            components: Default::default(),
            translation: RwLock::new(Vector3 {
                x: 0.0,
                y: 0.0,
                z: 0.0,
            }),
            rotation: RwLock::new(Quaternion {
                s: 0.0,
                v: Vector3 {
                    x: 0.0,
                    y: 0.0,
                    z: 0.0,
                },
            }),
            scale: RwLock::new(Vector3 {
                x: 0.0,
                y: 0.0,
                z: 0.0,
            }),
        }
    }
}

/// a piece of an entity representing a type of state and functionality associated with that state
pub trait EntityComponent: Debug + Send + Sync {
    /// process a render tick
    fn render(&self, entity: &Entity, delta: f64, services: &ServiceLocator);
    /// process an update tick
    fn update(
        &mut self,
        entity: &mut Entity,
        delta: f64,
        services: &ServiceLocator,
        game_state: &GameState,
    );
    /// process an input event
    fn handle_input(
        &mut self,
        entity: &mut Entity,
        event: &Event,
        services: &ServiceLocator,
        game_state: &GameState,
    );
}
