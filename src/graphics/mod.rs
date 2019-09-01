//! the graphics subsystem

use gfx_hal::Surface;
use std::cell::Cell;

#[cfg(not(target_arch = "wasm32"))]
use winit::Window;

pub mod window;

#[cfg(feature = "vulkan")]
pub mod vulkan;

#[cfg(feature = "gl")]
pub mod opengl;

#[cfg(feature = "metal")]
pub mod metal;

#[cfg(feature = "directx11")]
pub mod directx11;

#[cfg(feature = "directx12")]
pub mod directx12;

/// an object that can be rendered to a RenderTarget
pub trait Renderable {}

/// an object that can receive Renderable objects and render them
pub trait Surface {
    fn render(&mut self, subject: &dyn Renderable);
}

/// a framebuffer to which things can be rendered
pub struct NativeSurface<T> {}
impl RenderTarget for Surface<T> {
    fn render(&mut self, subject: &Renderable) {}
}
