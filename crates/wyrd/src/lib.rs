//! An Entity Component System Library

use std::any::{Any, TypeId};
use std::collections::{BTreeMap, HashMap};

pub type VecComponentStorage<T: Sized> = Vec<Option<T>>;
pub type HashMapComponentStorage<T: Sized> = HashMap<usize, T>;
pub type BTreeMapComponentStorage<T: Sized> = BTreeMap<usize, T>;

pub enum ComponentStorage<T: Sized> {
    Table(VecComponentStorage<T>),
    HashMap(HashMapComponentStorage<T>),
    BTreeMap(BTreeMapComponentStorage<T>),
}

#[derive(Default)]
pub struct Wyrd {
    component_storages: HashMap<TypeId, *mut ()>,
    entity_table: Vec<bool>,
}

impl Wyrd {
    pub fn register_component_type<T: 'static>(&mut self) {
        let mut data: VecComponentStorage<T> = VecComponentStorage::default();
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

    pub fn run_system(&self, component_types: &[TypeId], system: fn(Entity)) {
        for (i, meta) in self.entity_table.iter().enumerate() {
            if let true = meta {
                system(Entity::new(self, i))
            };
        }
    }

    fn get_component_storage<T: 'static + Sized>(&self) -> Option<&ComponentStorage<T>> {
        if let Some(pointer) = self.component_storages.get(&TypeId::of::<T>()) {
            unsafe { return pointer.cast::<ComponentStorage<T>>().as_ref() }
        }
        None
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
    wyrd: &'a Wyrd,
    index: usize,
}

impl<'a> Entity<'a> {
    fn new(wyrd: &'a Wyrd, index: usize) -> Self {
        Self { wyrd, index }
    }

    pub fn has_component<T: 'static>(&self) -> bool {
        matches!(self.get_component::<T>(), Some(_))
    }

    pub fn get_component<T: 'static>(&self) -> &'a Option<T> {
        if let Some(pointer) = self.wyrd.component_storages.get(&TypeId::of::<T>()) {
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
