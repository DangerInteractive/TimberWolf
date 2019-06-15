extern crate timberwolf;

use timberwolf::{Game};

fn main () {

    let game = Game::new();
    game.run(60, 20);

}
