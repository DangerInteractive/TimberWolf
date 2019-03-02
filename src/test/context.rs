//! unit test the context subsystem

use std::cell::RefCell;
use std::rc::Rc;
use crate::context::{Context, Story};

/// store record of whether a TestContext was rendered or updated
struct Status {
    rendered: bool,
    updated: bool
}

impl Status {

    fn new () -> Self {
        return Self {
            rendered: false,
            updated: false
        };
    }

    fn was_rendered (&self) -> bool {
        return self.rendered;
    }

    fn was_updated (&self) -> bool {
        return self.updated;
    }

    fn on_render (&mut self) {
        self.rendered = true;
    }

    fn on_update (&mut self) {
        self.updated = true;
    }

}

/// a context specifically designed for testing, and that reports its interactions to a Status
/// reference
struct TestContext {
    transparent_render: bool,
    transparent_update: bool,
    status: Rc<RefCell<Status>>
}

impl Context for TestContext {

    fn render (&mut self, _delta: f64) {
        self.status.borrow_mut().on_render();
    }

    fn update (&mut self, _delta: f64) {
        self.status.borrow_mut().on_update();
    }

    fn is_render_transparent (&self) -> bool {
        return self.transparent_render;
    }

    fn is_update_transparent (&self) -> bool {
        return self.transparent_update;
    }

}

impl TestContext {

    fn new (transparent_render: bool, transparent_update: bool, status: Rc<RefCell<Status>>) -> Self {
        return Self {
            transparent_render,
            transparent_update,
            status
        };
    }

}

#[test]
fn test_both_transparencies () {

    // monitor status
    let status_both = Rc::new(RefCell::new(Status::new()));
    let status_control = Rc::new(RefCell::new(Status::new()));

    {
        // create the experimental contexts
        let context_both = TestContext::new(true, true, status_both.clone());
        let context_control = TestContext::new(false, false, status_control.clone());

        // setup the story
        let mut story = Story::new();
        story.push_context(Box::new(context_control));
        story.push_context(Box::new(context_both));

        // simulate a render and update
        story.render(0f64);
        story.update(0f64);
    }

    // as top context, context_both receives both render and update
    assert!(status_both.borrow().was_rendered());
    assert!(status_both.borrow().was_updated());

    // context_both allows the render and update to pass through to control
    assert!(status_control.borrow().was_rendered());
    assert!(status_control.borrow().was_updated());

}

#[test]
fn test_render_transparency_only () {

    // monitor status
    let status_render = Rc::new(RefCell::new(Status::new()));
    let status_control = Rc::new(RefCell::new(Status::new()));

    {
        // create the experimental contexts
        let context_render = TestContext::new(true, false, status_render.clone());
        let context_control = TestContext::new(false, false, status_control.clone());

        // setup the story
        let mut story = Story::new();
        story.push_context(Box::new(context_control));
        story.push_context(Box::new(context_render));

        // simulate a render and update
        story.render(0f64);
        story.update(0f64);
    }

    // as top context, context_render receives both render and update
    assert!(status_render.borrow().was_rendered());
    assert!(status_render.borrow().was_updated());

    // context_render allows the render to pass through to control, but not update
    assert!(status_control.borrow().was_rendered());
    assert!(!status_control.borrow().was_updated());

}

#[test]
fn test_update_transparency_only () {

    // monitor status
    let status_update = Rc::new(RefCell::new(Status::new()));
    let status_control = Rc::new(RefCell::new(Status::new()));

    {
        // create the experimental contexts
        let context_update = TestContext::new(false, true, status_update.clone());
        let context_control = TestContext::new(false, false, status_control.clone());

        // setup the story
        let mut story = Story::new();
        story.push_context(Box::new(context_control));
        story.push_context(Box::new(context_update));

        // simulate a render and update
        story.render(0f64);
        story.update(0f64);
    }

    // as top context, context_update receives both render and update
    assert!(status_update.borrow().was_rendered());
    assert!(status_update.borrow().was_updated());

    // context_update allows the update to pass through to control, but not render
    assert!(!status_control.borrow().was_rendered());
    assert!(status_control.borrow().was_updated());

}

#[test]
fn test_both_opaque () {

    // monitor status
    let status_none = Rc::new(RefCell::new(Status::new()));
    let status_control = Rc::new(RefCell::new(Status::new()));

    {
        // create the experimental contexts
        let context_none = TestContext::new(false, false, status_none.clone());
        let context_control = TestContext::new(false, false, status_control.clone());

        // setup the story
        let mut story = Story::new();
        story.push_context(Box::new(context_control));
        story.push_context(Box::new(context_none));

        // simulate a render and update
        story.render(0f64);
        story.update(0f64);
    }

    // as top context, context_none receives both render and update
    assert!(status_none.borrow().was_rendered());
    assert!(status_none.borrow().was_updated());

    // context_none doesn't allow either render or update to pass through
    assert!(!status_control.borrow().was_rendered());
    assert!(!status_control.borrow().was_updated());

}

#[test]
fn test_deep_transparency () {

    // monitor status
    let status_both = Rc::new(RefCell::new(Status::new()));
    let status_render = Rc::new(RefCell::new(Status::new()));
    let status_control = Rc::new(RefCell::new(Status::new()));

    {
        // create the experimental contexts
        let context_both = TestContext::new(true, true, status_both.clone());
        let context_render = TestContext::new(true, false, status_render.clone());
        let context_control = TestContext::new(false, false, status_control.clone());

        // setup the story
        let mut story = Story::new();
        story.push_context(Box::new(context_control));
        story.push_context(Box::new(context_render));
        story.push_context(Box::new(context_both));

        // simulate a render and update
        story.update(0f64);
        story.render(0f64);
    }

    // as top context, context_both receives both render and update...
    assert!(status_both.borrow().was_rendered());
    assert!(status_both.borrow().was_updated());

    // context_both passes both update and render to context_render...
    assert!(status_render.borrow().was_rendered());
    assert!(status_render.borrow().was_updated());

    // context_render passes render to context_control, but not update
    assert!(status_control.borrow().was_rendered());
    assert!(!status_control.borrow().was_updated());

}

#[test]
fn test_overhang_occlusion () {

    // monitor status
    let status_both = Rc::new(RefCell::new(Status::new()));
    let status_render = Rc::new(RefCell::new(Status::new()));
    let status_update = Rc::new(RefCell::new(Status::new()));
    let status_control = Rc::new(RefCell::new(Status::new()));

    {
        // create the experimental contexts
        let context_both = TestContext::new(true, true, status_both.clone());
        let context_render = TestContext::new(true, false, status_render.clone());
        let context_update = TestContext::new(false, true, status_update.clone());
        let context_control = TestContext::new(false, false, status_control.clone());

        // setup the story
        let mut story = Story::new();
        story.push_context(Box::new(context_control));
        story.push_context(Box::new(context_update));
        story.push_context(Box::new(context_render));
        story.push_context(Box::new(context_both));

        // simulate a render and update
        story.update(0f64);
        story.render(0f64);
    }

    // as top context, context_both receives both render and update...
    assert!(status_both.borrow().was_rendered());
    assert!(status_both.borrow().was_updated());

    // context_both passes both update and render to context_render...
    assert!(status_render.borrow().was_rendered());
    assert!(status_render.borrow().was_updated());

    // context_render passes render to context_update, but not update...
    assert!(status_update.borrow().was_rendered());
    assert!(!status_update.borrow().was_updated());

    // context_update doesn't pass render, and is occluded from update by context_render, so
    // doesn't pass update to context_control
    assert!(!status_control.borrow().was_rendered());
    assert!(!status_control.borrow().was_updated());

}
