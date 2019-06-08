//! unit test the context subsystem

use crate::context::{Context, Story};
use std::cell::RefCell;
use std::rc::Rc;

/// store record of whether a TestContext was rendered or updated
struct Status {
    rendered: bool,
    updated: bool,
}

impl Status {

    fn new () -> Self {
        return Self {
            rendered: false,
            updated: false,
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
    status: Rc<RefCell<Status>>,
}

impl Context for TestContext {

    fn render (&mut self, _delta: f64) -> bool {
        self.status.borrow_mut().on_render();
        return true;
    }

    fn update (&mut self, _delta: f64) -> bool {
        self.status.borrow_mut().on_update();
        return true;
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
            status,
        };
    }

}

struct ContextSimulation {

    // configure the context
    render_transparent: bool,
    update_transparent: bool,

    // configure the assertions
    gets_rendered: bool,
    gets_updated: bool,

    // store the status
    status: Rc<RefCell<Status>>,

}
impl ContextSimulation {

    fn new (render_transparent: bool, update_transparent: bool, gets_rendered: bool, gets_updated: bool) -> Self {
        return Self {
            render_transparent,
            update_transparent,
            gets_rendered,
            gets_updated,
            status: Rc::new(RefCell::new(Status::new())),
        };
    }

}

fn simulate_with_asserts (context_simulations: &[ContextSimulation]) {

    // nothing has happened yet, so nothing should have been rendered or updated yet
    for csim in context_simulations {
        assert!(csim.status.borrow().was_rendered() == false);
        assert!(csim.status.borrow().was_updated() == false);
    }

    // run the simulation (in own scope due to mutable borrows)
    {
        let mut story = Story::new();

        for csim in context_simulations {
            story.push_context(Box::new(TestContext::new(
                csim.render_transparent,
                csim.update_transparent,
                csim.status.clone(),
            )));
        }

        story.render(0f64);
        story.update(0f64);
    }

    // check that things were rendered and updated as expected
    for csim in context_simulations {
        assert!(csim.status.borrow().was_rendered() == csim.gets_rendered);
        assert!(csim.status.borrow().was_updated() == csim.gets_updated);
    }
}

#[test]
fn test_both_transparencies () {
    simulate_with_asserts(&[
        // both render and update pass through to this one
        ContextSimulation::new(false, false, true, true),
        // top context gets rendered and updated
        ContextSimulation::new(true, true, true, true),
    ]);
}

#[test]
fn test_render_transparency_only () {
    simulate_with_asserts(&[
        // render passes through to this one, but not update
        ContextSimulation::new(false, false, true, false),
        // top context gets rendered and updated
        ContextSimulation::new(true, false, true, true),
    ]);
}

#[test]
fn test_update_transparency_only () {
    simulate_with_asserts(&[
        // update passes through to this one, but not render
        ContextSimulation::new(false, false, false, true),
        // top context gets rendered and updated
        ContextSimulation::new(false, true, true, true),
    ]);
}

#[test]
fn test_both_opaque () {
    simulate_with_asserts(&[
        // nothing passes through to this one
        ContextSimulation::new(false, false, false, false),
        // top context gets rendered and updated
        ContextSimulation::new(false, false, true, true),
    ]);
}

#[test]
fn test_deep_transparency () {
    simulate_with_asserts(&[
        // render passes through to this one, but not update
        ContextSimulation::new(false, false, true, false),
        // both render and update pass through to this one
        ContextSimulation::new(true, false, true, true),
        // top context gets rendered and updated
        ContextSimulation::new(true, true, true, true),
    ]);
}

#[test]
fn test_overhang_occlusion () {
    simulate_with_asserts(&[
        // nothing passes through to this one because the last one wasn't updated
        ContextSimulation::new(false, false, false, false),
        // render passes through to this one, but not update
        ContextSimulation::new(false, true, true, false),
        // both render and update pass through to this one
        ContextSimulation::new(true, false, true, true),
        // top context gets rendered and updated
        ContextSimulation::new(true, true, true, true),
    ]);
}
