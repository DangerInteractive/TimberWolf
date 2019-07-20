//! OpenGL graphics backend

use std::cell::{Cell};
use super::{NativeWindowBackend};

#[cfg(not(target_arch = "wasm32"))]
use winit::{Window};

#[cfg(feature = "gl")]
pub struct Backend {
    surface: Cell<Option<gfx_backend_gl::Surface>>
}
#[cfg(feature = "gl")]
impl Backend {

    pub fn new (name: &str, version: u32) -> Self {
        return Self {
            surface: Cell::new(None)
        }
    }

}
#[cfg(all(feature = "vulkan", not(target_arch = "wasm32")))]
impl NativeWindowBackend for Backend {

    fn bind_to_window (&self, window: &Window) {
        self.surface.set(gfx_backend_gl::Surface::from_window(window));
    }

}
