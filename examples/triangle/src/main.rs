use timberwolf::{
    lifecycle::{Command, Context},
    log::event::ConsoleReceiver,
    Game, GameState, ServiceLocator,
};
use winit::Event;

fn main() {
    let game = Game::new();
    game.get_services()
        .log
        .add_receiver(Box::new(ConsoleReceiver::new()));
    game.run(Box::new(LoadingContext::new()), 60, 20);
}

#[derive(Default)]
struct LoadingContext;
impl LoadingContext {
    /// create a new loading context
    pub fn new() -> Self {
        Default::default()
    }
}
impl Context for LoadingContext {
    fn render(&self, delta: f64, services: &ServiceLocator) -> Command {
        let message = format!("render delta: {}", delta);
        services.log.verbose("demo", &message);
        Command::Continue
    }
    fn update(&self, delta: f64, services: &ServiceLocator, _state: &GameState) -> Command {
        let message = format!("update delta: {}", delta);
        services.log.verbose("demo", &message);
        Command::Continue
    }
    fn handle_input(&self, event: Event, services: &ServiceLocator, _state: &GameState) -> Command {
        let message = format!("handle input: {:#?}", event);
        services.log.verbose("demo", &message);
        Command::Continue
    }
}
