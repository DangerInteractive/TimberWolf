//! subsystem for managing the different contexts of the game (AKA game states)

/// a context in which part of the game runs, also known as a game state
pub trait Context {

    /// whether or not this context allows lower contexts to render
    fn is_render_transparent (&self) -> bool {
        return false;
    }

    /// whether or not this context allows lower contexts to update
    fn is_update_transparent (&self) -> bool {
        return false;
    }

    /// whether or not this context allows lower contexts to receive input
    fn is_input_transparent (&self) -> bool {
        return false;
    }

    /// event indicating that the context has become the topmost context
    fn on_focus (&mut self) {}

    /// event indicating that the context is no longer the topmost context
    fn on_unfocus (&mut self) {}

    /// event indicating that the context has been pushed onto a story (and is given a reference to said story)
    fn on_push (&mut self, _story: &Story) {}

    /// event indicating that the context has been popped off of a story
    fn on_pop (&mut self) {}

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

    /// push a (boxed) context onto the top of the story
    pub fn push_context (&mut self, mut context: Box<Context>) {
        context.on_push(self);
        self.contexts.push(context);
    }

    /// pop the topmost context off of the story and return it
    pub fn pop_context (&mut self) -> Option<Box<Context>> {
        match self.contexts.pop() {
            Some (mut context) => {
                context.on_pop();
                return Some(context);
            }
            None => {
                return None
            }
        }
    }

    /// swrap the topmost context for a new one, and return the old one
    pub fn swap_context <T: 'static + Context> (&mut self, context: T) -> Option<Box<Context>> {
        let old_context = self.pop_context();
        self.push_context(Box::new(context));
        return old_context;
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
