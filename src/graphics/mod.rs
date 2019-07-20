//! the graphics subsystem

use std::cell::Cell;
use gfx_hal::Surface;

#[cfg(not(target_arch = "wasm32"))]
use winit::{Window};

pub mod window;

#[cfg(feature = "vulkan")]
pub mod vulkan;

#[cfg(feature = "gl")]
pub mod opengl;

#[cfg(not(target_arch = "wasm32"))]
pub trait NativeWindowBackend {
    fn bind_to_window (&self, window: &Window);
}
