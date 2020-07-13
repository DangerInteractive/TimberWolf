//! the subsystem that governs the event of the game engine

use std::fmt::Debug;
use std::slice::Iter;
use std::sync::Weak;

pub mod timing;

pub trait Observable {
    /// the event type that can be dispatched
    type NotificationType: Send + Sync + Debug;

    /// the response type expected from listeners
    type ResponseType: Send + Sync + Debug;

    /// dispatch a new event, and discard any response from the listeners
    fn notify_observers(&self, notification: Self::NotificationType);

    fn map_observers_with_notification(&self, notification: Self::NotificationType);
}

pub type Observer<T, R = ()> = fn(&T) -> R;

pub enum ObserverSlot<T, R = ()> {
    Empty,
    Owned(Box<Observer<T, R>>),
    Linked(Weak<Observer<T, R>>),
}

pub trait ObserverStorage {
    type NotificationType;
    type ResponseType;
    // TODO: type ResponseType = () // when defaulted associated types stabilize
    type Reader: Iterator<Item = ObserverSlot<Self::NotificationType, Self::ResponseType>>;

    fn iter(&self) -> Self::Reader;

    fn notify_observers(&self, notification: Self::NotificationType) {
        for listener in self.iter() {
            if let Some(listener) = match listener {
                ObserverSlot::Owned(listener) => Some(*listener),
                ObserverSlot::Linked(listener) => match listener.upgrade() {
                    Some(listener) => Some(*listener),
                    None => None,
                },
                ObserverSlot::Empty => None,
            } {
                &listener(&notification);
            }
        }
    }

    fn map_observers_with_notification(&self, notification: Self::NotificationType) {
        for listener in self.iter() {
            if let Some(listener) = match listener {
                ObserverSlot::Owned(listener) => Some(*listener),
                ObserverSlot::Linked(listener) => match listener.upgrade() {
                    Some(listener) => Some(*listener),
                    None => None,
                },
                Empty => None,
            } {
                listener(&notification);
            }
        }
    }
}

pub enum SetObserverError {
    ObserverAlreadySet,
}

pub trait SingleObserverStorage: ObserverStorage {
    fn set_observer(
        &mut self,
        observer: Weak<Observer<Self::NotificationType, Self::ResponseType>>,
    ) -> Result<(), SetObserverError>;
    fn set_observer_owned(
        &mut self,
        observer: Box<Observer<Self::NotificationType, Self::ResponseType>>,
    ) -> Result<(), SetObserverError>;
    fn clear_observer(&mut self);

    fn replace_observer(
        &mut self,
        observer: Weak<Observer<Self::NotificationType, Self::ResponseType>>,
    ) -> Result<(), SetObserverError> {
        self.clear_observer();
        self.set_observer(observer)
    }

    fn replace_observer_owned(
        &mut self,
        observer: Box<Observer<Self::NotificationType, Self::ResponseType>>,
    ) -> Result<(), SetObserverError> {
        self.clear_observer();
        self.set_observer_owned(observer)
    }
}

pub trait MultipleObserverStorage: ObserverStorage {
    fn add_observer(
        &mut self,
        observer: Weak<Observer<Self::NotificationType, Self::ResponseType>>,
    );
    fn add_observer_owned(
        &mut self,
        observer: Box<Observer<Self::NotificationType, Self::ResponseType>>,
    );
    fn clear_observers(&mut self);
}

pub struct VecObserverStorage<T, R = ()> {
    /// the active listeners
    event_listeners: Vec<ObserverSlot<T, R>>,
}
impl<T, R> VecObserverStorage<T, R> {
    pub fn new() -> Self {
        Self {
            event_listeners: vec![],
        }
    }
}
impl<'a, T: 'a, R: 'a> ObserverStorage for VecObserverStorage<T, R> {
    type NotificationType = T;
    type ResponseType = R;
    type Reader = Iter<'a, ObserverSlot<Self::NotificationType, Self::ResponseType>>;

    fn iter(&self) -> Self::Reader {
        self.event_listeners.iter()
    }
}
