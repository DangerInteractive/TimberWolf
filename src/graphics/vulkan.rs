//! Vulkan graphics backend

use crate::graphics::Context;
use gfx_backend::Instance::Surface as RawSurface;
use gfx_backend_vulkan as gfx_backend;

#[cfg(not(target_arch = "wasm32"))]
use winit::Window;

#[cfg(all(feature = "vulkan", not(target_arch = "wasm32")))]
pub struct Backend {
    instance: gfx_backend::Instance,
}
impl Backend {
    /// create a new instance of the Vulkan graphics backend
    pub fn new(name: &str, version: u32) -> Self {
        Self {
            instance: gfx_backend::Instance::create(name, version),
        }
    }

    /// create a new window surface from a window
    pub fn create_window_surface(&self, window: &Window) -> NativeSurface {
        NativeSurface {
            raw_surface: self.instance.create_surface(window),
        }
    }
}

pub struct Surface {
    raw_surface: RawSurface,
}
impl Context for Surface {
    fn clear_color_buffer(&mut self, color: &Color) {
        unimplemented!()
    }
    fn clear_depth_buffer(&mut self) {
        unimplemented!()
    }
    fn clear_all_buffers(&mut self, color: &Color) {
        unimplemented!()
    }
    fn render(&mut self, subject: &Renderable) {
        unimplemented!()
    }
}
