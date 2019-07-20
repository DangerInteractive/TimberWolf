//! Windowing subsystem

use std::string::{String};

#[cfg(not(target_arch = "wasm32"))]
use winit::{
    Window as WinitWindow,
    WindowBuilder as WinitWindowBuilder,
    EventsLoop as WinitEventLoop,
    dpi::{
        LogicalSize
    }
};

struct WindowSize {
    width: u16,
    height: u16
}

/// abstraction of an OS window
pub struct WindowBuilder {
    title: Option<String>,
    min_size: Option<WindowSize>,
    init_size: Option<WindowSize>,
    max_size: Option<WindowSize>
}
impl WindowBuilder {

    /// create a new window, given a name, min/max width/height, and current width/height
    pub fn new () -> Self {
        return Self {
            title: None,
            min_size: None,
            init_size: None,
            max_size: None
        };
    }

    pub fn with_title (&mut self, title: &str) -> &mut Self {
        self.title = Some(String::from_str(title));
        return self;
    }

    pub fn with_minimum_size (&mut self, width: u16, height: u16) -> &mut Self {
        self.min_size = Some(WindowSize{ width, height });
        return self;
    }

    pub fn with_initial_size (&mut self, width: u16, height: u16) -> &mut Self {
        self.init_size = Some(WindowSize{ width, height });
        return self;
    }

    pub fn with_maximum_size (&mut self, width: u16, height: u16) -> &mut Self {
        self.max_size = Some(WindowSize{ width, height });
        return self;
    }

    /// create a native window context
    pub fn into_native (self) -> NativeWindow {
        let event_loop = WinitEventLoop::new();
        return NativeWindow {
            winit: self.to_native_builder()
                .build(&event_loop)
                .expect("cannot create winit window"),
            event_loop
        }
    }

    /// create an OpenGL-specific window context (because OpenGL does things differently)
    #[cfg(feature = "gl")]
    pub fn into_opengl (self) -> OpenGLWindow {
        let event_loop = WinitEventLoop::new();
        return OpenGLWindow {
            context: gfx_backend_gl::glutin::WindowedContext::new_windowed(
                self.to_native_builder(),
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

    fn to_native_builder (&self) -> WinitWindowBuilder {
        let mut wb = WinitWindowBuilder::new();

        // conditionally set the title
        match &self.title {
            Some (title) => wb.with_title(title),
            None => ()
        };

        // conditionally set the minimum size
        match &self.min_size {
            Some (dimensions) => wb.with(
                LogicalSize::new(
                    dimensions.width as _,
                    dimensions.height as _
                )
            ),
            None => ()
        };

        // conditionally set the initial size
        match &self.init_size {
            Some (dimensions) => wb.with_dimensions(
                LogicalSize::new(
                    dimensions.width as _,
                    dimensions.height as _
                )
            ),
            None => ()
        };

        // conditionally set the maximum size
        match &self.max_size {
            Some (dimensions) => wb.with_max_dimensions(
                LogicalSize::new(
                    dimensions.width as _,
                    dimensions.height as _
                )
            ),
            None => ()
        };

        return wb;

    }

}

/// handle for a native window (not WebAssembly, not OpenGL)
#[cfg(not(target_arch = "wasm32"))]
pub struct NativeWindow {
    winit: WinitWindow,
    event_loop: WinitEventLoop
}

/// handle for an OpenGL window (because it does things a little differently)
#[cfg(feature = "gl")]
pub struct OpenGLWindow {
    context: gfx_backend_gl::glutin::WindowedContext,
    event_loop: WinitEventLoop
}
