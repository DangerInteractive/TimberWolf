#include "GameState.hpp"

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
