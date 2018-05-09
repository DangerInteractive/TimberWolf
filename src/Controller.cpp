#include "../include/Controller.hpp"

/**
 * @class tw::Controller
 *
 * Container for storing and processing input event handlers such as keybindings
 * and mouse button presses. Instances are stored in tw::GameState objects.
 */

tw::Controller::Controller () {}

/**
 * Notify key callbacks of a key press event.
 *
 * @param action   0 means key was released, 1 means key was pressed, 2 means key was held
 * @param mod      key modifier
 * @param key      engine key code
 * @param scanCode OS key scan code
 */
void tw::Controller::onKey (int action, int mod, int key, int scanCode) {

    for (int i = 0; i < m_keybindings.size(); ++i) {
        m_keybindings[i].process(action, mod, key, scanCode);
    }
    Log::verbose("input", "Key ", action, " ", mod, " ", key, " ", scanCode);

}

/**
 * Notify cursor move callbacks of a cursor move event.
 *
 * @param xPos horizontal pixel of cursor position from left side
 * @param yPos vertical pixel of cursor position from top side
 */
void tw::Controller::onCursor (double xPos, double yPos) {

    Log::verbose("input", "Mouse ", xPos, " ", yPos);

}

/**
 * Notify cursor entry callbacks of a cursor enter event.
 */
void tw::Controller::onCursorIn () {

    Log::verbose("input", "Mouse In");

}

/**
 * Notify cursor exit callbacks of a cursor exit event.
 */
void tw::Controller::onCursorOut () {

    Log::verbose("input", "Mouse Out");

}

/**
 * Notify mouse button callbacks of a mouse button event.
 *
 * @param action 0 means button was released, 1 means button was pressed
 * @param mod    key modifier
 * @param button 0 means left button, 1 means right button, 2 means center button
 */
void tw::Controller::onMouseButton (int action, int mod, int button) {

    Log::verbose("input", "Mouse Button ", action, " ", mod, " ", button);

}

/**
 * Notify scroll callbacks of a scroll event.
 *
 * @param xOffset horizontal scroll position in pixels
 * @param yOffset vertical scroll position in pixels
 */
void tw::Controller::onScroll (double xOffset, double yOffset) {

    Log::verbose("input", "Scroll ", xOffset, " ", yOffset);

}

/**
 * Notify file drop callbacks of a file drop event.
 *
 * @param count number of files dropped
 * @param paths raw array of dropped file paths
 */
void tw::Controller::onDrop (int count, const char** paths) {

    Log::verbose("input", "Drop ", count, " ", *paths);

}

/**
 * Get a std::vector of all attached keybindings.
 *
 * @return keybindings
 */
std::vector<tw::Keybinding> tw::Controller::getKeybindings () {

    return m_keybindings;

}

/**
 * Get a std::vector of all attached keybindings matching specified parameters.
 *
 * @param action   0 means key release, 1 means key press, 2 means key hold
 * @param mod      key modifier
 * @param key      engine key code
 * @param scanCode OS key scan code
 * @return keybindings
 */
std::vector<tw::Keybinding> tw::Controller::getKeybindings (KeyAction action, KeyMod mod, KeyType key, int scanCode) {

    std::vector<Keybinding> out;

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (
            action == m_keybindings[i].getAction() &&
            mod.getFlags() == m_keybindings[i].getMod().getFlags() &&
            (
                key == m_keybindings[i].getKey() ||
                scanCode == m_keybindings[i].getScanCode()
            )
        ) {
            out.push_back(m_keybindings[i]);
        }

    }

    return out;

}

/**
 * Get a std::vector of all attached keybindings matching specified key action.
 *
 * @param action 0 means key release, 1 means key press, 2 means key hold
 * @return keybindings
 */
std::vector<tw::Keybinding> tw::Controller::getKeybindingsByKeyAction (KeyAction action) {

    std::vector<Keybinding> out;

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (action == m_keybindings[i].getAction()) {
            out.push_back(m_keybindings[i]);
        }

    }

    return out;

}

/**
 * Get a std::vector of all attached keybindings matching specified key type.
 *
 * @param key engine key code
 * @return keybindings
 */
std::vector<tw::Keybinding> tw::Controller::getKeybindingsByKeyType (KeyType key) {

    std::vector<Keybinding> out;

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (key == m_keybindings[i].getKey()) {
            out.push_back(m_keybindings[i]);
        }

    }

    return out;

}

/**
 * Get a std::vector of all attached keybindings matching specified key
 * modifier.
 *
 * @param mod key modifier
 * @return keybindings
 */
std::vector<tw::Keybinding> tw::Controller::getKeybindingsByKeyMod (KeyMod mod) {

    std::vector<Keybinding> out;

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (mod == m_keybindings[i].getMod()) {
            out.push_back(m_keybindings[i]);
        }

    }

    return out;

}

/**
 * Get a std::vector of all attached keybindings matching specified OS key scan
 * code.
 *
 * @param scanCode OS key scan code
 * @return keybindings
 */
std::vector<tw::Keybinding> tw::Controller::getKeybindingsByScanCode (int scanCode) {

    std::vector<Keybinding> out;

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (scanCode == m_keybindings[i].getScanCode()) {
            out.push_back(m_keybindings[i]);
        }

    }

    return out;

}

/**
 * Replace all attached keybindings with a given std::vector of keybindings.
 *
 * @param keybindings new keybindings
 */
void tw::Controller::setKeybindings (const std::vector<Keybinding>& keybindings) {

    m_keybindings = keybindings;

}

/**
 * Add keybinding to the existing attached keybindings.
 *
 * @param keybinding keybinding to attach
 */
void tw::Controller::addKeybinding (const Keybinding& keybinding) {

    m_keybindings.push_back(keybinding);

}

/**
 * Remove all attached keybindings.
 */
void tw::Controller::clearKeybindings () {

    m_keybindings.clear();

}

/**
 * Remove all attached keybindings matching specified parameters.
 *
 * @param action   0 means key release, 1 means key press, 2 means key hold
 * @param mod      key modifier
 * @param key      engine key code
 * @param scanCode OS key scan code
 */
void tw::Controller::removeKeybindings (KeyAction action, KeyMod mod, KeyType key, int scanCode) {

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (
            action == m_keybindings[i].getAction() &&
            mod.getFlags() == m_keybindings[i].getMod().getFlags() &&
            (
                key == m_keybindings[i].getKey() ||
                scanCode == m_keybindings[i].getScanCode()
            )
        ) {
            m_keybindings.erase(m_keybindings.begin() + i);
            --i;
        }

    }

}

/**
 * Remove all attached keybindings matching specified key actions.
 *
 * @param action 0 means key release, 1 means key press
 */
void tw::Controller::removeKeybindingsByKeyAction (KeyAction action) {

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (action == m_keybindings[i].getAction()) {
            m_keybindings.erase(m_keybindings.begin() + i);
            --i;
        }

    }

}

/**
 * Remove all attached keybindings matching specified key type.
 *
 * @param key engine key code
 */
void tw::Controller::removeKeybindingsByKeyType (KeyType key) {

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (key == m_keybindings[i].getKey()) {
            m_keybindings.erase(m_keybindings.begin() + i);
            --i;
        }

    }

}

/**
 * Remove all attached keybindings matching specified key modifier.
 *
 * @param mod key modifier
 */
void tw::Controller::removeKeybindingsByKeyMod (KeyMod mod) {

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (mod == m_keybindings[i].getMod()) {
            m_keybindings.erase(m_keybindings.begin() + i);
            --i;
        }

    }

}

/**
 * Remove all attached keybindings matching specified OS key scan code.
 *
 * @param scanCode OS key scan code
 */
void tw::Controller::removeKeybindingsByScanCode (int scanCode) {

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (scanCode == m_keybindings[i].getScanCode()) {
            m_keybindings.erase(m_keybindings.begin() + i);
            --i;
        }

    }

}

/**
 * Get a std::vector of cursor move callbacks.
 *
 * @return cursor move callbacks
 */
std::vector<tw::Controller::CursorCallback> tw::Controller::getCursorCallbacks () {

    return m_cursorCallbacks;

}

/**
 * Replace all cursor move callbacks with a given std::vector of cursor move
 * callbacks.
 *
 * @param cursorCallbacks new cursor move callbacks
 */
void tw::Controller::setCursorCallbacks (const std::vector<Controller::CursorCallback>& cursorCallbacks) {

    m_cursorCallbacks = cursorCallbacks;

}

/**
 * Attach a cursor move callback.
 *
 * @param cursorCallback cursor move callback to attach
 */
void tw::Controller::addCursorCallback (const Controller::CursorCallback& cursorCallback) {

    m_cursorCallbacks.push_back(cursorCallback);

}

/**
 * Remove all attached cursor move callbacks.
 */
void tw::Controller::clearCursorCallbacks () {

    m_cursorCallbacks.clear();

}

/**
 * Get a std::vector of cursor entry callbacks.
 *
 * @return cursor entry callbacks
 */
std::vector<tw::Controller::CursorInCallback> tw::Controller::getCursorInCallbacks () {

    return m_cursorInCallbacks;

}

/**
 * Replace all attached cursor entry callbacks with a given std::vector of
 * cursor entry callbacks.
 *
 * @param cursorInCallbacks cursor entry callbacks
 */
void tw::Controller::setCursorInCallbacks (const std::vector<Controller::CursorInCallback>& cursorInCallbacks) {

    m_cursorInCallbacks = cursorInCallbacks;

}

/**
 * Attach a cursor entry callback.
 *
 * @param cursorInCallback cursor entry callback to attach
 */
void tw::Controller::addCursorInCallback (const Controller::CursorInCallback& cursorInCallback) {

    m_cursorInCallbacks.push_back(cursorInCallback);

}

/**
 * Remove all attached cursor entry callbacks.
 */
void tw::Controller::clearCursorInCallbacks () {

    m_cursorInCallbacks.clear();

}

/**
 * Get a std::vector of all attached cursor exit callbacks.
 *
 * @return cursor exit callbacks
 */
std::vector<tw::Controller::CursorOutCallback> tw::Controller::getCursorOutCallbacks () {

    return m_cursorOutCallbacks;

}

/**
 * Replace all attached cursor exit callbacks with a given std::vector of cursor
 * exit callbacks.
 *
 * @param cursorOutCallbacks new cursor exit callbacks
 */
void tw::Controller::setCursorOutCallbacks (const std::vector<Controller::CursorOutCallback>& cursorOutCallbacks) {

    m_cursorOutCallbacks = cursorOutCallbacks;

}

/**
 * Attach a cursor exit callback.
 *
 * @param cursorOutCallback cursor exit callback to attach
 */
void tw::Controller::addCursorOutCallback (const Controller::CursorOutCallback& cursorOutCallback) {

    m_cursorOutCallbacks.push_back(cursorOutCallback);

}

/**
 * Remove all attached cursor exit callbacks.
 */
void tw::Controller::clearCursorOutCallbacks () {

    m_cursorOutCallbacks.clear();

}

/**
 * Get a std::vector of all attached window focus callbacks.
 *
 * @return window focus callbacks
 */
std::vector<tw::Controller::FocusCallback> tw::Controller::getFocusCallbacks () {

    return m_focusCallbacks;

}

/**
 * Replace all attached window focus callbacks with a given std::vector of
 * window focus callbacks.
 *
 * @param focusCallbacks new window focus callbacks
 */
void tw::Controller::setFocusCallbacks (const std::vector<Controller::FocusCallback>& focusCallbacks) {

    m_focusCallbacks = focusCallbacks;

}

/**
 * Attach a window focus callback.
 *
 * @param focusCallback window focus callback to attach
 */
void tw::Controller::addFocusCallback (const Controller::FocusCallback& focusCallback) {

    m_focusCallbacks.push_back(focusCallback);

}

/**
 * Remove all attached window focus callbacks.
 */
void tw::Controller::clearFocusCallbacks () {

    m_focusCallbacks.clear();

}

/**
 * Get a std::vector of all attached window unfocus callbacks.
 *
 * @return window unfocus callbacks
 */
std::vector<tw::Controller::UnfocusCallback> tw::Controller::getUnfocusCallbacks () {

    return m_unfocusCallbacks;

}

/**
 * Replace all attached window unfocus callbacks with a given std::vector of
 * window unfocus callbacks.
 *
 * @param unfocusCallbacks window unfocus callbacks
 */
void tw::Controller::setUnfocusCallbacks (const std::vector<Controller::UnfocusCallback>& unfocusCallbacks) {

    m_unfocusCallbacks = unfocusCallbacks;

}

/**
 * Attach a window unfocus callback.
 *
 * @param unfocusCallback window unfocus callback to attach
 */
void tw::Controller::addUnfocusCallback (const Controller::UnfocusCallback& unfocusCallback) {

    m_unfocusCallbacks.push_back(unfocusCallback);

}

/**
 * Remove all attached window unfocus callbacks.
 */
void tw::Controller::clearUnfocusCallbacks () {

    m_unfocusCallbacks.clear();

}

/**
 * Get a std::vector of attached mouse button press callbacks.
 *
 * @return mouse button press callbacks
 */
std::vector<tw::Controller::MouseButtonPressCallback> tw::Controller::getMouseButtonPressCallbacks () {

    return m_mouseButtonPressCallbacks;

}

/**
 * Replace all attached mouse button press callbacks with a given std::vector of
 * mouse button press callbacks.
 *
 * @param mouseButtonPressCallbacks new mouse button press callbacks
 */
void tw::Controller::setMouseButtonPressCallbacks (const std::vector<Controller::MouseButtonPressCallback>& mouseButtonPressCallbacks) {

    m_mouseButtonPressCallbacks = mouseButtonPressCallbacks;

}

/**
 * Attach mouse button press callback.
 *
 * @param mouseButtonPressCallback mouse button press callback to add
 */
void tw::Controller::addMouseButtonPressCallback (const Controller::MouseButtonPressCallback& mouseButtonPressCallback) {

    m_mouseButtonPressCallbacks.push_back(mouseButtonPressCallback);

}

/**
 * Remove all attached mouse button press callbacks.
 */
void tw::Controller::clearMouseButtonPressCallbacks () {

    m_mouseButtonPressCallbacks.clear();

}

/**
 * Get a std::vector of all attached mouse button release callbacks.
 *
 * @return mouse button release callbacks
 */
std::vector<tw::Controller::MouseButtonReleaseCallback> tw::Controller::getMouseButtonReleaseCallbacks () {

    return m_mouseButtonReleaseCallbacks;

}

/**
 * Replace all attached mouse button release callbacks with a given std::vector
 * of mouse button release callbacks.
 *
 * @param mouseButtonReleaseCallbacks new mouse button release callbacks
 */
void tw::Controller::setMouseButtonReleaseCallbacks (const std::vector<Controller::MouseButtonReleaseCallback>& mouseButtonReleaseCallbacks) {

    m_mouseButtonReleaseCallbacks = mouseButtonReleaseCallbacks;

}

/**
 * Attach a mouse button release callback
 *
 * @param mouseButtonReleaseCallback mouse button release callback to add
 */
void tw::Controller::addMouseButtonReleaseCallback (const MouseButtonReleaseCallback& mouseButtonReleaseCallback) {

    m_mouseButtonReleaseCallbacks.push_back(mouseButtonReleaseCallback);

}

/**
 * Remove all attached mouse button release callbacks.
 */
void tw::Controller::clearMouseButtonReleaseCallbacks () {

    m_mouseButtonReleaseCallbacks.clear();

}

/**
 * Get a std::vector of all attached scroll callbacks.
 *
 * @return scroll callbacks
 */
std::vector<tw::Controller::ScrollCallback> tw::Controller::getScrollCallbacks () {

    return m_scrollCallbacks;

}

/**
 * Replace all attached scroll callbacks with a given std::vector of scroll
 * callbacks.
 *
 * @param scrollCallbacks new scroll callbacks
 */
void tw::Controller::setScrollCallbacks (const std::vector<ScrollCallback>& scrollCallbacks) {

    m_scrollCallbacks = scrollCallbacks;

}

/**
 * Attach a new scroll callback.
 *
 * @param scrollCallback scroll callback to attach
 */
void tw::Controller::addScrollCallback (const ScrollCallback& scrollCallback) {

    m_scrollCallbacks.push_back(scrollCallback);

}

/**
 * Clear all attached scroll callbacks.
 */
void tw::Controller::clearScrollCallbacks () {

    m_scrollCallbacks.clear();

}

/**
 * Get a std::vector of all attached window resize callbacks.
 *
 * @return window resize callbacks
 */
std::vector<tw::Controller::ResizeCallback> tw::Controller::getResizeCallbacks () {

    return m_resizeCallbacks;

}

/**
 * Replace all attached window resize callbacks with a given std::vector of
 * window resize callbacks.
 *
 * @param resizeCallbacks new window resize callbacks
 */
void tw::Controller::setResizeCallbacks (const std::vector<ResizeCallback>& resizeCallbacks) {

    m_resizeCallbacks = resizeCallbacks;

}

/**
 * Attach a window resize callback.
 *
 * @param resizeCallback window resize callback to attach
 */
void tw::Controller::addResizeCallback (const ResizeCallback& resizeCallback) {

    m_resizeCallbacks.push_back(resizeCallback);

}

/**
 * Remove all attached window resize callbacks.
 */
void tw::Controller::clearResizeCallbacks () {

    m_resizeCallbacks = {};

}
