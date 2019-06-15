extern crate timberwolf;

use timberwolf::{Game, context::{Context, Request}, log::{Log}};

fn main () {

    let mut game = Game::new();
    game.push_story_context(Box::new(LoadingContext::new()));
    game.run(60, 20);

}

struct LoadingContext;
impl LoadingContext {

    fn new () -> Self {
        return Self;
    }

}
impl Context for LoadingContext {

    fn is_render_transparent (&self) -> bool { false }
    fn is_update_transparent (&self) -> bool { false }
    fn is_input_transparent  (&self) -> bool { false }

    fn render (&self, delta: f64, log: &Log) -> Request {
        let message = format!("render delta: {}", delta);
        log.verbose("demo", &message);
        Request::Continue
    }

    fn update (&mut self, delta: f64, log: &Log) -> Request {
        let message = format!("update delta: {}", delta);
        log.verbose("demo", &message);
        Request::Continue
    }

}
