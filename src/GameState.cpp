#include "../include/GameState.hpp"

/**
 * @class tw::GameState
 *
 * Abstract class representing a state of the game state machine. This class is
 * meant to be extended by child classes which implement the logic of its
 * respective state of the game.
 */

void tw::GameState::clearWindow () {

    if (m_clearWindow) {
        Window::clear(m_clearColor);
    }

}

tw::Controller& tw::GameState::getController () {

    return m_controller;

}

void tw::GameState::setController (Controller& controller) {

    m_controller = controller;

}

void tw::GameState::clearController () {

    m_controller = Controller();

}
