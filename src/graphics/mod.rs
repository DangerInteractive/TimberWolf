//! graphics subsystem

use cgmath::{Matrix4, Vector2, Vector3};
use std::sync::Arc;

pub mod rendy;

/// something that is capable of rendering models
pub trait Renderer {
    /// draw a model to the renderer
    fn render_model(mesh: Model, transform: Matrix4<f32>);
}

/// a three-dimensional object and its textures
pub struct Model {
    /// the three-dimensional surface of the model
    pub mesh: Arc<Mesh>,
    /// the base color texture
    pub texture_base_color: Option<Arc<Texture>>,
}

/// a three-dimensional surface represented by a lot of triangles strung together
#[derive(Default, Debug)]
pub struct Mesh {
    /// a vector of vertex coordinates and their associated data
    pub vertices: Vec<Vertex>,
    /// a vector of indices to the vertices field, allowing more efficient duplicate usage of the same
    pub indices: Vec<u32>,
}

/// the spatial and texture coordinates of a three-dimensional vertex
#[derive(Debug)]
pub struct Vertex {
    /// the three-dimensional spatial coordinates of the vertex
    pub spatial: Vector3<f32>,
    /// the two-dimensional texture coordinate of the vertex
    pub texture: Vector2<f32>,
}
impl Default for Vertex {
    fn default() -> Self {
        Self {
            spatial: Vector3 {
                x: 0.0,
                y: 0.0,
                z: 0.0,
            },
            texture: Vector2 { x: 0.0, y: 0.0 },
        }
    }
}

/// an image that is supposed to be mapped onto the surface of a mesh
pub struct Texture {}
