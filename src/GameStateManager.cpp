#include "../include/GameStateManager.hpp"

void tw::GameStateManager::pushState (const std::shared_ptr<GameState>& state) {

    m_states.push_back(state);
    state->onPush();
    state->onActivate();

    if (m_states.size() > 1) {
        auto prev = m_states[m_states.size() - 2];
        prev->onDeactivate();
        for (int i = m_states.size() - 2; i >= 0; --i) {
            m_states[i]->onDescend();
        }
    }

    refreshLiveStates();

}

void tw::GameStateManager::pushState (GameState* state) {

    std::shared_ptr<GameState> ptrState(state);
    pushState(ptrState);

}

bool tw::GameStateManager::pushState (const std::string& key) {

    if (!GameStateStore::stateExists(key)) {
        return false;
    }

    auto state = GameStateStore::getState(key);
    pushState(state);

    return true;

}

void tw::GameStateManager::dropState () {

    auto top = m_states[m_states.size() - 1];
    top->onDeactivate();
    top->onPop();
    top.reset();

    if (m_states.size() > 0) {
        auto top = m_states[m_states.size() - 1];
        top->onActivate();
        for (int i = m_states.size() - 1; i >= 0; --i) {
            m_states[i]->onAscend();
        }
    }

    refreshLiveStates();

}

std::shared_ptr<tw::GameState> tw::GameStateManager::popState () {

    auto top = m_states[m_states.size() - 1];
    top->onDeactivate();
    top->onPop();

    if (m_states.size() > 0) {
        auto top = m_states[m_states.size() - 1];
        top->onActivate();
        for (int i = m_states.size() - 1; i >= 0; --i) {
            m_states[i]->onAscend();
        }
    }

    refreshLiveStates();

    return top;

}

void tw::GameStateManager::refreshLiveStates () {

    std::vector<std::shared_ptr<GameState>> liveRenderStates;
    std::vector<std::shared_ptr<GameState>> liveUpdateStates;
    std::vector<std::shared_ptr<GameState>> liveInputStates;

    auto top = m_states[m_states.size() - 1];
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

        auto prev = top;
        bool renderBroken = !prev->transparentRender;
        bool updateBroken = !prev->transparentUpdate;
        bool inputBroken = !prev->transparentInput;

        for (int i = m_states.size() - 2; i >= 0; --i) {

            auto cur = m_states[i];

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

void tw::GameStateManager::clearWindow () {

    for (int i = m_statesLiveRender.size() - 1; i >= 0; --i) {
        m_statesLiveRender[i]->clearWindow();
    }

}

void tw::GameStateManager::render (double deltaTime) {

    for (int i = 0; i < m_statesLiveRender.size(); ++i) {
        m_statesLiveRender[i]->render(deltaTime);
    }

}

void tw::GameStateManager::update (double deltaTime) {

    for (int i = 0; i < m_statesLiveUpdate.size(); ++i) {
        m_statesLiveUpdate[i]->update(deltaTime);
    };

}

void tw::GameStateManager::keyCallback (GLFWwindow* window, int key, int scanCode, int action, int mod) {

    for (int i = 0; i < m_statesLiveInput.size(); ++i) {
        m_statesLiveInput[i]->getController().onKey(action, mod, key, scanCode);
    };

}

void tw::GameStateManager::cursorCallback (GLFWwindow* window, double xPos, double yPos) {

    for (int i = 0; i < m_statesLiveInput.size(); ++i) {
        m_statesLiveInput[i]->getController().onCursor(xPos, yPos);
    }

}

void tw::GameStateManager::cursorInOutCallback (GLFWwindow* window, int in) {

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

void tw::GameStateManager::mouseButtonCallback (GLFWwindow* window, int button, int action, int mod) {

    for (int i = 0; i < m_statesLiveInput.size(); ++i) {
        m_statesLiveInput[i]->getController().onMouseButton(action, mod, button);
    }

}

void tw::GameStateManager::scrollCallback (GLFWwindow* window, double xOffset, double yOffset) {

    for (int i = 0; i < m_statesLiveInput.size(); ++i) {
        m_statesLiveInput[i]->getController().onScroll(xOffset, yOffset);
    }

}

void tw::GameStateManager::dropCallback (GLFWwindow* window, int count, const char** paths) {

    for (int i = 0; i < m_statesLiveInput.size(); ++i) {
        m_statesLiveInput[i]->getController().onDrop(count, paths);
    }

}

std::vector<std::shared_ptr<tw::GameState>> tw::GameStateManager::m_states;

std::vector<std::shared_ptr<tw::GameState>> tw::GameStateManager::m_statesLiveRender;
std::vector<std::shared_ptr<tw::GameState>> tw::GameStateManager::m_statesLiveUpdate;
std::vector<std::shared_ptr<tw::GameState>> tw::GameStateManager::m_statesLiveInput;
