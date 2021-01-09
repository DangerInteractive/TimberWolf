//! the subsystem that governs the event of the game engine

use std::fmt::Debug;
use std::slice::Iter;
use std::sync::Weak;

pub mod timing;

/// an event emitter which other objects can observe
pub trait Observable {
    /// the event type that can be dispatched
    type NotificationType: Send + Sync + Debug;

    /// dispatch a new event, and discard any response from the listeners
    fn notify_observers(&self, notification: Self::NotificationType);
}

/// a function which can observe an `Observable<T>`
pub type Observer<T> = fn(&T);

/// storage for observers, allowing varied ownership and to allow observers to drop before the observable as needed
pub enum ObserverSlot<T> {
    /// no observer present, can be populated with a new one
    Empty,
    /// an observer which is owned by the observable (will not drop until the observable does, which could cause memory leaks if that's not what you want)
    Owned(Box<Observer<T>>),
    /// an observer which is owned elsewhere and can be dropped spontaneously
    Linked(Weak<Observer<T>>),
}

/// a storage capable of holding one or more observers and iterating over them
pub trait ObserverStorage<'a> {
    /// the type which is sent to each of the observers whenever they are notified
    type NotificationType: 'a;
    /// the storage iterator type
    type Reader: Iterator<Item = &'a ObserverSlot<Self::NotificationType>>;

    /// iterate over the observer slots
    fn iter(&'a self) -> Self::Reader;

    /// dispatch a notification to each of the observers
    fn notify_observers(&'a self, notification: Self::NotificationType) {
        for observer_slot in self.iter() {
            match observer_slot {
                ObserverSlot::Owned(observer) => {
                    observer(&notification);
                }
                ObserverSlot::Linked(observer) => {
                    if let Some(linked_observer) = observer.upgrade() {
                        linked_observer(&notification);
                    };
                }
                ObserverSlot::Empty => (),
            };
        }
    }
}

/// an error returned when set observer fails (for single-observables)
pub enum SetObserverError {
    /// the observer has already been set, and must be cleared before another can be set
    ObserverAlreadySet,
}

/// storage for observables that can only hold a single observer
pub trait SingleObserverStorage<'a>: ObserverStorage<'a> {
    /// set the observer to a linked (weak) observer
    fn set_observer(
        &mut self,
        observer: Weak<Observer<Self::NotificationType>>,
    ) -> Result<(), SetObserverError>;
    /// set the observer to an owned (boxed) observer
    fn set_observer_owned(
        &mut self,
        observer: Box<Observer<Self::NotificationType>>,
    ) -> Result<(), SetObserverError>;
    /// clear the set observer, or no-op if not set
    fn clear_observer(&mut self);

    /// replace the observer with a linked (weak) observer, equivalent to `clear_observer` followed by `set_observer`
    fn replace_observer(
        &mut self,
        observer: Weak<Observer<Self::NotificationType>>,
    ) -> Result<(), SetObserverError> {
        self.clear_observer();
        self.set_observer(observer)
    }

    /// replace the observer with an owned (boxed) observer, equivalent to `clear_observer` followed by `set_observer`
    fn replace_observer_owned(
        &mut self,
        observer: Box<Observer<Self::NotificationType>>,
    ) -> Result<(), SetObserverError> {
        self.clear_observer();
        self.set_observer_owned(observer)
    }
}

/// storage for observables that can hold multiple observers
pub trait MultipleObserverStorage<'a>: ObserverStorage<'a> {
    /// add a linked (weak) observer
    fn add_observer(&mut self, observer: Weak<Observer<Self::NotificationType>>);
    /// add an owned (boxed) observer
    fn add_observer_owned(&mut self, observer: Box<Observer<Self::NotificationType>>);
    /// clear all stored observers
    fn clear_observers(&mut self);
}

/// a multi-observable storage backed by Vec
#[derive(Default)]
pub struct VecObserverStorage<T> {
    /// the active listeners
    event_listeners: Vec<ObserverSlot<T>>,
}
impl<T> VecObserverStorage<T> {
    fn push_observer_slot(&mut self, observer_slot: ObserverSlot<T>) {
        if let Some(matched_observer_slot) = self
            .event_listeners
            .iter_mut()
            .find(|observer_slot| matches!(observer_slot, ObserverSlot::Empty))
        {
            *matched_observer_slot = observer_slot;
            return;
        }

        self.event_listeners.push(observer_slot)
    }
}
impl<'a, T: 'a> ObserverStorage<'a> for VecObserverStorage<T> {
    type NotificationType = T;
    type Reader = Iter<'a, ObserverSlot<T>>;

    fn iter(&'a self) -> Self::Reader {
        self.event_listeners.iter()
    }
}
impl<'a, T: 'a> MultipleObserverStorage<'a> for VecObserverStorage<T> {
    fn add_observer(&mut self, observer: Weak<fn(&Self::NotificationType)>) {
        self.push_observer_slot(ObserverSlot::Linked(observer))
    }

    fn add_observer_owned(&mut self, observer: Box<fn(&Self::NotificationType)>) {
        self.push_observer_slot(ObserverSlot::Owned(observer))
    }

    fn clear_observers(&mut self) {
        self.event_listeners.clear()
    }
}
