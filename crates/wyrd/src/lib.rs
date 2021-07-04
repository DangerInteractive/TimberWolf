//! An Entity Component System Library

use std::any::{Any, TypeId};
use std::collections::HashMap;

#[derive(Default)]
pub struct Wyrd {
    component_storages: ComponentStorageMap,
    entity_meta: Vec<EntityMeta>,
}

pub enum EntityMeta {
    Empty,
    Active,
}

pub type ComponentStorageMap = HashMap<TypeId, *mut ()>;
pub type ComponentStorage<T> = Vec<Option<T>>;

impl Wyrd {
    pub fn register_component_type<T: 'static>(&mut self) {
        let mut data: ComponentStorage<T> = ComponentStorage::default();
        self.component_storages
            .insert(TypeId::of::<T>(), data.as_mut_ptr().cast::<()>());
    }

    // pub fn spawn_entity(&self, entity: BuiltEntity) {
    //     for (type_id, component) in entity.builder.components.iter() {
    //         if let Some(storage) = self.component_storages.get(type_id) {
    //             let real_storage = unsafe { storage.cast::<ComponentStorage<type_id>>()}
    //         }
    //     }
    // }

    pub fn run_system(&self, system: fn(Entity)) {
        for (i, meta) in self.entity_meta.iter().enumerate() {
            if let EntityMeta::Active = meta {
                system(Entity::new(&self.component_storages, i))
            };
        }
    }
}

#[derive(Default)]
pub struct EntityBuilder {
    components: HashMap<TypeId, Box<dyn Any>>,
}

impl EntityBuilder {
    pub fn add_component<T: 'static>(&mut self, component: Box<T>) -> &mut Self {
        self.components.insert(TypeId::of::<T>(), component);
        self
    }

    pub fn build(self) -> EntityConfig {
        EntityConfig { builder: self }
    }
}

pub struct EntityConfig {
    builder: EntityBuilder,
}

pub struct Entity<'a> {
    storage: &'a ComponentStorageMap,
    index: usize,
}

impl<'a> Entity<'a> {
    fn new(storage: &'a ComponentStorageMap, index: usize) -> Self {
        Self { storage, index }
    }

    pub fn has_component<T: 'static>(&mut self) -> bool {
        matches!(self.get_component::<T>(), Some(_))
    }

    pub fn get_component<T: 'static>(&mut self) -> &'a Option<T> {
        if let Some(pointer) = self.storage.get(&TypeId::of::<T>()) {
            unsafe {
                if let Some(storage) = pointer.cast::<Vec<Option<T>>>().as_ref() {
                    if let Some(component) = storage.get(self.index) {
                        component
                    } else {
                        &None
                    }
                } else {
                    &None
                }
            }
        } else {
            &None
        }
    }
}
