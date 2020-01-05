//! renderer that utilizes Rendy

use rendy::{
    core::hal,
    factory::{BasicDevicesConfigure, BasicHeapsConfigure, Config, OneGraphicsQueue},
    init::Rendy,
};
use std::sync::Arc;
use winit::Window;

/// a renderer that can render stuff to a window using Rendy
pub struct WindowRenderer<Backend: hal::Backend> {
    /// the window to which the renderer will render
    pub window: Arc<Window>,
    /// the instance of Rendy
    pub instance: Rendy<Backend>,
}
impl<Backend: hal::Backend> WindowRenderer<Backend> {
    /// create a new Rendy renderer for a given window
    pub fn new(window: Arc<Window>) -> Self {
        Self {
            window,
            instance: Rendy::init(&Config {
                devices: BasicDevicesConfigure::default(),
                heaps: BasicHeapsConfigure::default(),
                queues: OneGraphicsQueue::default(),
            })
            .expect("failed to create a rendy instance"),
        }
    }
}
