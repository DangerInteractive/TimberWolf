//! subsystem for managing the different contexts of the game (AKA game states)

/// a context in which part of the game runs, also known as a game state
pub trait Context {

    /// whether or not this context allows lower contexts to render
    fn is_render_transparent (&self) -> bool;

    /// whether or not this context allows lower contexts to update
    fn is_update_transparent (&self) -> bool;

    /// whether or not this context allows lower contexts to receive input
    fn is_input_transparent (&self) -> bool;

    /// event indicating that the context has become the topmost context
    fn on_focus (&mut self);

    /// event indicating that the context is no longer the topmost context
    fn on_unfocus (&mut self);

    /// event indicating that the context has been pushed onto a stack
    fn on_push (&mut self);

    /// event indicating that the context has been popped off of a stack
    fn on_pop (&mut self);

    /// render the visual portion of the context according to a number of seconds since the last update call
    fn render (&mut self, delta: f64);

    /// update the state of the context according to a number of passed seconds
    fn update (&mut self, delta: f64);

}

/// a stack-like collection of contexts that determines which controls what and when contexts do things
pub struct Story {

    /// an ordered list of contexts from bottom to top
    contexts: Vec<Box<Context>>

}

impl Story {

    /// create a new context story
    pub fn new () -> Self {
        return Self {
            contexts: vec![]
        }
    }

    /// render the visual portion of the story (which means to correctly render the contexts it contains)
    pub fn render (&mut self, delta: f64) {

        // create a list of contexts to be rendered by searching in reverse order
        let mut to_render = vec![];
        for context in self.contexts.iter_mut().rev() {
            let opaque = !context.is_render_transparent();
            to_render.push(context);
            if opaque {
                break;
            }
        }

        // render those contexts in forward order
        for context in to_render {
            context.render(delta);
        }

    }

    /// update the state portion of the story (which means to correctly update the state of the contexts it contains)
    pub fn update (&mut self, delta: f64) {

        // create a list of contexts to be updated by searching in reverse order
        let mut to_update = vec![];
        for context in self.contexts.iter_mut().rev() {
            let opaque = !context.is_update_transparent();
            to_update.push(context);
            if opaque {
                break;
            }
        }

        // render those contexts in forward order
        for context in to_update {
            context.update(delta);
        }

    }

}
