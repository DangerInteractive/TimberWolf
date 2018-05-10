#include "../include/GameState.hpp"

/**
 * @class tw::GameState
 *
 * Abstract class representing a state of the game state machine. This class is
 * meant to be extended by child classes which implement the logic of its
 * respective state of the game.
 */

/**
 * Clear the window.
 */
void tw::GameState::clearWindow () {

    if (m_clearWindow) {
        Window::clear(m_clearColor);
    }

}

/**
 * Get the attached tw::Controller, which handles input.
 *
 * @return controller (input handler)
 */
tw::Controller& tw::GameState::getController () {

    return m_controller;

}

/**
 * Replace the attached controller.
 *
 * @param controller controller (input handler)
 */
void tw::GameState::setController (Controller& controller) {

    m_controller = controller;

}

/**
 * Remove the attached controller.
 */
void tw::GameState::clearController () {

    m_controller = Controller();

}
