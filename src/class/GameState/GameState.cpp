#include "GameState.hpp"

Controller& GameState::getController () {

    return m_controller;

}

void GameState::setController (Controller& controller) {

    m_controller = controller;

}

void GameState::clearController () {

    m_controller = Controller();

}
