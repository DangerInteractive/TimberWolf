#include "GameStateManager.hpp"

void GameStateManager::pushState (GameState* state) {

    m_states.push_back(state);
    state->onPush();
    state->onActivate();

    if (m_states.size() > 1) {
        GameState* prev = m_states[m_states.size() - 2];
        prev->onDeactivate();
        for (int i = m_states.size() - 2; i >= 0; --i) {
            m_states[i]->onDescend();
        }
    }

    refreshLiveStates();

}

bool GameStateManager::pushState (std::string key) {

    if (!GameStateStore::stateExists(key)) {
        return false;
    }

    GameState* state = GameStateStore::getState(key);
    pushState(state);

    return true;

}

void GameStateManager::dropState () {

    GameState* top = m_states[m_states.size() - 1];
    top->onDeactivate();
    top->onPop();
    delete top;

    if (m_states.size() > 0) {
        GameState* top = m_states[m_states.size() - 1];
        top->onActivate();
        for (int i = m_states.size() - 1; i >= 0; --i) {
            m_states[i]->onAscend();
        }
    }

    refreshLiveStates();

}

GameState* GameStateManager::popState () {

    GameState* top = m_states[m_states.size() - 1];
    top->onDeactivate();
    top->onPop();

    if (m_states.size() > 0) {
        GameState* top = m_states[m_states.size() - 1];
        top->onActivate();
        for (int i = m_states.size() - 1; i >= 0; --i) {
            m_states[i]->onAscend();
        }
    }

    refreshLiveStates();

    return top;

}

void GameStateManager::refreshLiveStates () {

    std::vector<GameState*> liveRenderStates;
    std::vector<GameState*> liveUpdateStates;
    std::vector<GameState*> liveInputStates;

    GameState* top = m_states[m_states.size() - 1];
    liveRenderStates.push_back(top);
    liveUpdateStates.push_back(top);
    liveInputStates.push_back(top);

    if (
        m_states.size() > 1 &&
        (
            top->transparentRender ||
            top->transparentUpdate ||
            top->transparentInput
        )
    ) {

        GameState* prev = top;
        bool renderBroken = !prev->transparentRender;
        bool updateBroken = !prev->transparentUpdate;
        bool inputBroken = !prev->transparentInput;

        for (int i = m_states.size() - 2; i >= 0; --i) {

            GameState* cur = m_states[i];

            if (renderBroken && updateBroken && inputBroken) {
                break;
            }

            if (prev->transparentRender) {
                liveRenderStates.push_back(cur);
            } else {
                renderBroken = true;
            }

            if (prev->transparentUpdate) {
                liveUpdateStates.push_back(cur);
            } else {
                updateBroken = true;
            }

            if (prev->transparentInput) {
                liveInputStates.push_back(cur);
            } else {
                inputBroken = true;
            }

            prev = m_states[i];

        }

    }

    m_statesLiveRender = liveRenderStates;
    m_statesLiveUpdate = liveUpdateStates;
    m_statesLiveInput = liveInputStates;

}

void GameStateManager::render (double deltaTime) {

    for (int i = 0; i < m_statesLiveRender.size(); ++i) {
        m_statesLiveRender[i]->render(deltaTime);
    }

}

void GameStateManager::update () {

    for (int i = 0; i < m_statesLiveUpdate.size(); ++i) {
        m_statesLiveUpdate[i]->update();
    };

}

void GameStateManager::keyCallback (GLFWwindow* window, int key, int scanCode, int action, int mod) {

    for (int i = 0; i < m_statesLiveInput.size(); ++i) {
        m_statesLiveInput[i]->getController().onKey(action, mod, key, scanCode);
    };

}

void GameStateManager::cursorCallback (GLFWwindow* window, double xPos, double yPos) {

    for (int i = 0; i < m_statesLiveInput.size(); ++i) {
        m_statesLiveInput[i]->getController().onCursor(xPos, yPos);
    }

}

void GameStateManager::cursorInOutCallback (GLFWwindow* window, int in) {

    if (in) {
        for (int i = 0; i < m_statesLiveInput.size(); ++i) {
            m_statesLiveInput[i]->getController().onCursorIn();
        }
    } else {
        for (int i = 0; i < m_statesLiveInput.size(); ++i) {
            m_statesLiveInput[i]->getController().onCursorOut();
        }
    }

}

void GameStateManager::mouseButtonCallback (GLFWwindow* window, int button, int action, int mod) {

    for (int i = 0; i < m_statesLiveInput.size(); ++i) {
        m_statesLiveInput[i]->getController().onMouseButton(action, mod, button);
    }

}

void GameStateManager::scrollCallback (GLFWwindow* window, double xOffset, double yOffset) {

    for (int i = 0; i < m_statesLiveInput.size(); ++i) {
        m_statesLiveInput[i]->getController().onScroll(xOffset, yOffset);
    }

}

void GameStateManager::dropCallback (GLFWwindow* window, int count, const char** paths) {

    for (int i = 0; i < m_statesLiveInput.size(); ++i) {
        m_statesLiveInput[i]->getController().onDrop(count, paths);
    }

}

std::vector<GameState*> GameStateManager::m_states;

std::vector<GameState*> GameStateManager::m_statesLiveRender;
std::vector<GameState*> GameStateManager::m_statesLiveUpdate;
std::vector<GameState*> GameStateManager::m_statesLiveInput;
