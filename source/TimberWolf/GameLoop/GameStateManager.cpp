#include "../../../include/TimberWolf/GameLoop/GameStateManager.hpp"

/**
 * @class tw::GameStateManager
 *
 * Static class representing the game state machine, a pushdown automaton type
 * state machine for switching game states during game runtime. Stores shared
 * pointers to GameState objects polymorphically.
 */

/**
 * Push a std::shared_ptr to a game state onto the stack.
 *
 * @param state game state to push
 */
void tw::GameStateManager::pushState (const std::shared_ptr<GameState>& state) {

    m_states.push_back(state);
    state->onPush();
    state->onActivate();

    if (m_states.size() > 1) {
        auto prev = m_states[m_states.size() - 2];
        prev->onDeactivate();
        for (unsigned int i = m_states.size() - 1; i > 0; --i) {
            m_states[i - 1]->onDescend();
        }
    }

    refreshLiveStates();

}

/**
 * Push a pointer to a game state onto the stack.
 *
 * @param state game state
 */
void tw::GameStateManager::pushState (GameState* state) {

    std::shared_ptr<GameState> ptrState(state);
    pushState(ptrState);

}

/**
 * Push a game state onto the stack via a key to a game state stored in
 * tw::GameStateStore. Will fail if there is no matching game state registered
 * with tw::GameStateStore before calling.
 *
 * @param key key to game state stored in tw::GameStateStore
 * @return true if game state was found and pushed, false if not
 */
bool tw::GameStateManager::pushState (const std::string& key) {

    if (!GameStateStore::stateExists(key)) {
        return false;
    }

    auto state = GameStateStore::getState(key);
    pushState(state);

    return true;

}

/**
 * Pop and dispose of the top (current) game state on the stack, switching to
 * the next lower state if it exists.
 */
void tw::GameStateManager::dropState () {

    auto top = m_states[m_states.size() - 1];
    top->onDeactivate();
    top->onPop();
    top.reset();

    if (m_states.size() > 0) {
        auto top = m_states[m_states.size() - 1];
        top->onActivate();
        for (unsigned int i = m_states.size(); i > 0; --i) {
            m_states[i - 1]->onAscend();
        }
    }

    refreshLiveStates();

}

/**
 * Pop and return the top (current) game state on the stack, switching to the
 * next lower state if it exists.
 *
 * @return shared pointer to the popped state
 */
std::shared_ptr<tw::GameState> tw::GameStateManager::popState () {

    auto top = m_states[m_states.size() - 1];
    top->onDeactivate();
    top->onPop();

    if (m_states.size() > 0) {
        auto top = m_states[m_states.size() - 1];
        top->onActivate();
        for (unsigned int i = m_states.size(); i > 0; --i) {
            m_states[i - 1]->onAscend();
        }
    }

    refreshLiveStates();

    return top;

}

/**
 * Refresh the cached lists of states that are eligible for processing based on
 * their transparency flags. This is automatically called whenever the game
 * state stack is changed.
 */
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

        for (unsigned int i = m_states.size() - 1; i > 0; --i) {

            auto cur = m_states[i - 1];

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

            prev = m_states[i - 1];

        }

    }

    m_statesLiveRender = liveRenderStates;
    m_statesLiveUpdate = liveUpdateStates;
    m_statesLiveInput = liveInputStates;

}

/**
 * Execute an iteration of the active game state(s) render loop, passing the
 * number of seconds since the last iteration of the update loop for the purpose
 * of preventing rendering stutter. This should only be called by tw::GameLoop.
 *
 * @param deltaTime number of seconds perceived since the last iteration of the update loop
 */
void tw::GameStateManager::render (double deltaTime) {

    for (unsigned int i = 0; i < m_statesLiveRender.size(); ++i) {
        m_statesLiveRender[i]->render(deltaTime);
    }

}

/**
 * Execute an iteration of the active game state(s) update loop, passing the
 * number of seconds perceived since the last iteration to the update loop. This
 * should only be called by tw::GameLoop.
 *
 * @param deltaTime number of seconds perceived since the last iteration of the update loop
 */
void tw::GameStateManager::update (double deltaTime) {

    for (unsigned int i = 0; i < m_statesLiveUpdate.size(); ++i) {
        m_statesLiveUpdate[i]->update(deltaTime);
    };

}

/**
 * Notify the active state(s) of a key input event. This is a callback passed
 * directly to GLFW. You shouldn't need to call it unless you need to simulate
 * a key input event.
 *
 * @param window   pointer to the window context
 * @param key      engine key code
 * @param scanCode OS key scan code
 * @param action   0 for release, 1 for press, 2 for hold
 * @param mod      key modifier
 */
void tw::GameStateManager::keyCallback (GLFWwindow* window, int key, int scanCode, int action, int mod) {

    for (unsigned int i = 0; i < m_statesLiveInput.size(); ++i) {
        m_statesLiveInput[i]->getController().onKey(action, mod, key, scanCode);
    };

}

/**
 * Notify the active state(s) of a cursor move event. This is a callback passed
 * directly to GLFW. You shouldn't need to call it unless you need to simulate
 * a cursor move event.
 *
 * @param window pointer to window context
 * @param xPos   horizontal position of cursor in pixels from left
 * @param yPos   vertical position of cursor in pixels from top
 */
void tw::GameStateManager::cursorCallback (GLFWwindow* window, double xPos, double yPos) {

    for (unsigned int i = 0; i < m_statesLiveInput.size(); ++i) {
        m_statesLiveInput[i]->getController().onCursor(xPos, yPos);
    }

}

/**
 * Notify the active state(s) of a cursor entry or exit event. This is a
 * callback passed directly to GLFW. You shouldn't need to call it unless you
 * need to simulate a cursor entry or exit event.
 *
 * @param window pointer to window context
 * @param in     [description]
 */
void tw::GameStateManager::cursorInOutCallback (GLFWwindow* window, int in) {

    if (in) {
        for (unsigned int i = 0; i < m_statesLiveInput.size(); ++i) {
            m_statesLiveInput[i]->getController().onCursorIn();
        }
    } else {
        for (unsigned int i = 0; i < m_statesLiveInput.size(); ++i) {
            m_statesLiveInput[i]->getController().onCursorOut();
        }
    }

}

/**
 * Notify the active state(s) of a mouse button input event. This is a callback
 * passed directly to GLFW. You shouldn't need to call it unless you need to
 * simulate a mouse button event.
 *
 * @param window pointer to window context
 * @param button 0 for left, 1 for right, 2 for middle
 * @param action 0 for release, 1 for press
 * @param mod    key modifier
 */
void tw::GameStateManager::mouseButtonCallback (GLFWwindow* window, int button, int action, int mod) {

    for (unsigned int i = 0; i < m_statesLiveInput.size(); ++i) {
        m_statesLiveInput[i]->getController().onMouseButton(action, mod, button);
    }

}

/**
 * Notify the active state(s) of a scroll event. This is a callback passed
 * directly to GLFW. You shouldn't need to call it unless you need to simulate
 * a scroll event.
 *
 * @param window  pointer to window context
 * @param xOffset horizontal scroll position in pixels from left
 * @param yOffset vertical scroll position in pixels from top
 */
void tw::GameStateManager::scrollCallback (GLFWwindow* window, double xOffset, double yOffset) {

    for (unsigned int i = 0; i < m_statesLiveInput.size(); ++i) {
        m_statesLiveInput[i]->getController().onScroll(xOffset, yOffset);
    }

}

/**
 * Notify the active state(s) of a file drop event. This is a callback passed
 * directly to GLFW. You shouldn't need to call it unless you need to simulate a
 * file drop event.
 *
 * @param window pointer to window context
 * @param count  number of files dropped
 * @param paths  array of file paths for the dropped files
 */
void tw::GameStateManager::dropCallback (GLFWwindow* window, int count, const char** paths) {

    for (unsigned int i = 0; i < m_statesLiveInput.size(); ++i) {
        m_statesLiveInput[i]->getController().onDrop(count, paths);
    }

}

std::vector<std::shared_ptr<tw::GameState>> tw::GameStateManager::m_states; ///< Game state stack, actually a std::vector so state transparency can iterate.

std::vector<std::shared_ptr<tw::GameState>> tw::GameStateManager::m_statesLiveRender; ///< Ordered game states eligible to be rendered (based on game state transparencies). This is a cache.
std::vector<std::shared_ptr<tw::GameState>> tw::GameStateManager::m_statesLiveUpdate; ///< Ordered game states eligible to be updated (based on game state transparencies). This is a cache.
std::vector<std::shared_ptr<tw::GameState>> tw::GameStateManager::m_statesLiveInput; ///< Ordered game states eligible to receive input events (based on game state transparencies). This is a cache.
