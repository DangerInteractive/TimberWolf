//! Vulkan graphics backend

use std::cell::{Cell};
use gfx_hal::{Surface};
use super::{NativeWindowBackend};

#[cfg(not(target_arch = "wasm32"))]
use winit::{Window};

#[cfg(feature = "vulkan")]
pub struct Backend {
    instance: gfx_backend_vulkan::Instance,
    surface: Cell<Option<Surface<gfx_backend_vulkan::Instance>>>
}
#[cfg(feature = "vulkan")]
impl Backend {

    /// create a new instance of the Vulkan graphics backend
    pub fn new (name: &str, version: u32) -> Self {
        return Self {
            instance: gfx_backend_vulkan::Instance::create(name, version),
            surface: Cell::new(None)
        }
    }

}
#[cfg(all(feature = "vulkan", not(target_arch = "wasm32")))]
impl NativeWindowBackend for Backend {

    fn bind_to_window (&self, window: &Window) {
        self.surface.set(self.instance.create_surface(window));
    }

}
