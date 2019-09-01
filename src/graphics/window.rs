//! Windowing subsystem

use std::string::String;
use gfx_hal::format::{Rgba8Srgb as ColorFormat};

#[cfg(not(target_arch = "wasm32"))]
use winit::{
    Window as Winit_Window,
    WindowBuilder as Winit_WindowBuilder,
    EventsLoop as Winit_EventsLoop
};

struct Size {
    pub height: u16,
    pub width: u16
}

pub struct Window {
    title: Option<String>,
    size: Option<Size>,
    min_size: Option<Size>,
    max_size: Option<Size>
}
impl Window {

    pub fn new () -> Self {
        Self {
            title: None,
            size: None,
            min_size: None,
            max_size: None,
        }
    }

}

/// handle for a native window (not WebAssembly, not OpenGL)
#[cfg(not(target_arch = "wasm32"))]
pub struct NativeWindow {
    /// the winit window object
    pub context: Window,
    /// the winit event loop
    pub event_loop: EventsLoop
}
impl NativeWindow {

    /// create a new native window, given a winit WindowBuilder
    fn new (wb: WindowBuilder) -> Self {
        let event_loop = WinitEventLoop::new();
        return Self {
            context: wb
                .build(&event_loop)
                .expect("cannot create winit window"),
            event_loop
        }
    }

}

/// handle for an OpenGL window (because it does things a little differently)
#[cfg(all(not(target_arch = "wasm32"), feature = "gl"))]
pub struct OpenGLWindow {
    /// the glutin window context
    pub context: gfx_backend_gl::glutin::WindowedContext,
    /// the winit event loop
    pub event_loop: WinitEventLoop
}
impl OpenGLWindow {

    /// create a new OpenGL-specific window, given a winit WindowBuilder
    fn new (wb: WindowBuilder) -> Self {
        let event_loop = WinitEventLoop::new();
        return Self {
            context: gfx_backend_gl::glutin::WindowedContext::new_windowed(
                wb,
                gfx_backend_gl::config_context(
                    gfx_backend_gl::glutin::ContextBuilder::new(),
                    ColorFormat::SELF,
                    None
                ).with_vsync(true),
                &event_loop
            ).expect("cannot create OpenGL context"),
            event_loop
        }
    }

}
