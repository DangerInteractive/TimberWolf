//! the graphics subsystem

use gfx_hal::Surface as RawSurface;
use std::cell::Cell;

use crate::color::Color;
#[cfg(not(target_arch = "wasm32"))]
use winit::Window;

#[cfg(feature = "directx11")]
pub mod directx11;
#[cfg(feature = "directx12")]
pub mod directx12;
#[cfg(feature = "metal")]
pub mod metal;
#[cfg(feature = "gl")]
pub mod opengl;
#[cfg(feature = "vulkan")]
pub mod vulkan;
pub mod window;

/// an object that can be rendered to a Context
pub trait Renderable {}

/// an object that can receive Renderable objects and render them
pub trait Context {
    /// clear the context's color buffer
    fn clear_color_buffer(&mut self, color: &Color);
    /// clear the context's depth buffer
    fn clear_depth_buffer(&mut self);
    /// clear the context's color and depth buffer
    fn clear_all_buffers(&mut self, color: &Color);
    /// render the given Renderable on top of the context
    fn render(&mut self, subject: &dyn Renderable);
}
