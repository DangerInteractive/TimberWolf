//! OpenGL graphics backend

use std::cell::{Cell};
use gfx_backend_gl as gfx_backend;

#[cfg(not(target_arch = "wasm32"))]
use winit::{Window};

#[cfg(feature = "gl")]
pub struct Backend {
}
#[cfg(feature = "gl")]
impl Backend {

    pub fn new () -> Self {
        Self {}
    }

}
