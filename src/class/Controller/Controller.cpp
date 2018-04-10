#include "Controller.hpp"

Controller::Controller () {}

void Controller::onKey (int action, int mod, int key, int scanCode) {

    for (int i = 0; i < m_keybindings.size(); ++i) {
        m_keybindings[i].process(action, mod, key, scanCode);
    }
    Log::verbose("input", "Key ", action, " ", mod, " ", key, " ", scanCode);

}

void Controller::onCursor (double xPos, double yPos) {

    Log::verbose("input", "Mouse ", xPos, " ", yPos);

}

void Controller::onCursorIn () {

    Log::verbose("input", "Mouse In");

}

void Controller::onCursorOut () {

    Log::verbose("input", "Mouse Out");

}

void Controller::onMouseButton (int action, int mod, int button) {

    Log::verbose("input", "Mouse Button ", action, " ", mod, " ", button);

}

void Controller::onScroll (double xOffset, double yOffset) {

    Log::verbose("input", "Scroll ", xOffset, " ", yOffset);

}

void Controller::onDrop (int count, const char** paths) {

    Log::verbose("input", "Drop ", count, " ", *paths);

}

std::vector<Keybinding> Controller::getKeybindings () {

    return m_keybindings;

}

std::vector<Keybinding> Controller::getKeybindings (KeyAction action, KeyMod mod, KeyType key, int scanCode) {

    std::vector<Keybinding> out;

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (
            action == m_keybindings[i].m_action &&
            mod.getFlags() == m_keybindings[i].m_mod.getFlags() &&
            (
                key == m_keybindings[i].m_key ||
                scanCode == m_keybindings[i].m_scanCode
            )
        ) {
            out.push_back(m_keybindings[i]);
        }

    }

    return out;

}

std::vector<Keybinding> Controller::getKeybindingsByKeyAction (KeyAction action) {

    std::vector<Keybinding> out;

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (action == m_keybindings[i].m_action) {
            out.push_back(m_keybindings[i]);
        }

    }

    return out;

}

std::vector<Keybinding> Controller::getKeybindingsByKeyType (KeyType key) {

    std::vector<Keybinding> out;

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (key == m_keybindings[i].m_key) {
            out.push_back(m_keybindings[i]);
        }

    }

    return out;

}

std::vector<Keybinding> Controller::getKeybindingsByKeyMod (KeyMod mod) {

    std::vector<Keybinding> out;

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (mod == m_keybindings[i].m_mod) {
            out.push_back(m_keybindings[i]);
        }

    }

    return out;

}

std::vector<Keybinding> Controller::getKeybindingsByScanCode (int scanCode) {

    std::vector<Keybinding> out;

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (scanCode == m_keybindings[i].m_scanCode) {
            out.push_back(m_keybindings[i]);
        }

    }

    return out;

}

void Controller::setKeybindings (const std::vector<Keybinding>& keybindings) {

    m_keybindings = keybindings;

}

void Controller::addKeybinding (const Keybinding& keybinding) {

    m_keybindings.push_back(keybinding);

}

void Controller::clearKeybindings () {

    m_keybindings = {};

}

void Controller::removeKeybindings (KeyAction action, KeyMod mod, KeyType key, int scanCode) {

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (
            action == m_keybindings[i].m_action &&
            mod.getFlags() == m_keybindings[i].m_mod.getFlags() &&
            (
                key == m_keybindings[i].m_key ||
                scanCode == m_keybindings[i].m_scanCode
            )
        ) {
            m_keybindings.erase(m_keybindings.begin() + i);
            --i;
        }

    }

}

void Controller::removeKeybindingsByKeyAction (KeyAction action) {

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (action == m_keybindings[i].m_action) {
            m_keybindings.erase(m_keybindings.begin() + i);
            --i;
        }

    }

}

void Controller::removeKeybindingsByKeyType (KeyType key) {

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (key == m_keybindings[i].m_key) {
            m_keybindings.erase(m_keybindings.begin() + i);
            --i;
        }

    }

}

void Controller::removeKeybindingsByKeyMod (KeyMod mod) {

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (mod == m_keybindings[i].m_mod) {
            m_keybindings.erase(m_keybindings.begin() + i);
            --i;
        }

    }

}

void Controller::removeKeybindingsByScanCode (int scanCode) {

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (scanCode == m_keybindings[i].m_scanCode) {
            m_keybindings.erase(m_keybindings.begin() + i);
            --i;
        }

    }

}

std::vector<Controller::CursorCallback> Controller::getCursorCallbacks () {

    return m_cursorCallbacks;

}

void Controller::setCursorCallbacks (const std::vector<Controller::CursorCallback>& cursorCallbacks) {

    m_cursorCallbacks = cursorCallbacks;

}

void Controller::addCursorCallback (const Controller::CursorCallback& cursorCallback) {

    m_cursorCallbacks.push_back(cursorCallback);

}

void Controller::clearCursorCallbacks () {

    m_cursorCallbacks = {};

}

std::vector<Controller::CursorInCallback> Controller::getCursorInCallbacks () {

    return m_cursorInCallbacks;

}

void Controller::setCursorInCallbacks (const std::vector<Controller::CursorInCallback>& cursorInCallbacks) {

    m_cursorInCallbacks = cursorInCallbacks;

}

void Controller::addCursorInCallback (const Controller::CursorInCallback& cursorInCallback) {

    m_cursorInCallbacks.push_back(cursorInCallback);

}

void Controller::clearCursorInCallbacks () {

    m_cursorInCallbacks = {};

}

std::vector<Controller::CursorOutCallback> Controller::getCursorOutCallbacks () {

    return m_cursorOutCallbacks;

}

void Controller::setCursorOutCallbacks (const std::vector<Controller::CursorOutCallback>& cursorOutCallbacks) {

    m_cursorOutCallbacks = cursorOutCallbacks;

}

void Controller::addCursorOutCallback (const Controller::CursorOutCallback& cursorOutCallback) {

    m_cursorOutCallbacks.push_back(cursorOutCallback);

}

void Controller::clearCursorOutCallbacks () {

    m_cursorOutCallbacks = {};

}

std::vector<Controller::FocusCallback> Controller::getFocusCallbacks () {

    return m_focusCallbacks;

}

void Controller::setFocusCallbacks (const std::vector<Controller::FocusCallback>& focusCallbacks) {

    m_focusCallbacks = focusCallbacks;

}

void Controller::addFocusCallback (const Controller::FocusCallback& focusCallback) {

    m_focusCallbacks.push_back(focusCallback);

}

void Controller::clearFocusCallbacks () {

    m_focusCallbacks = {};

}

std::vector<Controller::UnfocusCallback> Controller::getUnfocusCallbacks () {

    return m_unfocusCallbacks;

}

void Controller::setUnfocusCallbacks (const std::vector<Controller::UnfocusCallback>& unfocusCallbacks) {

    m_unfocusCallbacks = unfocusCallbacks;

}

void Controller::addUnfocusCallback (const Controller::UnfocusCallback& unfocusCallback) {

    m_unfocusCallbacks.push_back(unfocusCallback);

}

void Controller::clearUnfocusCallbacks () {

    m_unfocusCallbacks = {};

}

std::vector<Controller::MouseButtonPressCallback> Controller::getMouseButtonPressCallbacks () {

    return m_mouseButtonPressCallbacks;

}

void Controller::setMouseButtonPressCallbacks (const std::vector<Controller::MouseButtonPressCallback>& mouseButtonPressCallbacks) {

    m_mouseButtonPressCallbacks = mouseButtonPressCallbacks;

}

void Controller::addMouseButtonPressCallback (const Controller::MouseButtonPressCallback& mouseButtonPressCallback) {

    m_mouseButtonPressCallbacks.push_back(mouseButtonPressCallback);

}

void Controller::clearMouseButtonPressCallbacks () {

    m_mouseButtonPressCallbacks = {};

}

std::vector<Controller::MouseButtonReleaseCallback> Controller::getMouseButtonReleaseCallbacks () {

    return m_mouseButtonReleaseCallbacks;

}

void Controller::setMouseButtonReleaseCallbacks (const std::vector<Controller::MouseButtonReleaseCallback>& mouseButtonReleaseCallbacks) {

    m_mouseButtonReleaseCallbacks = mouseButtonReleaseCallbacks;

}

void Controller::addMouseButtonReleaseCallback (const Controller::MouseButtonReleaseCallback& mouseButtonReleaseCallback) {

    m_mouseButtonReleaseCallbacks.push_back(mouseButtonReleaseCallback);

}

void Controller::clearMouseButtonReleaseCallbacks () {

    m_mouseButtonReleaseCallbacks = {};

}

std::vector<Controller::ScrollCallback> Controller::getScrollCallbacks () {

    return m_scrollCallbacks;

}

void Controller::setScrollCallbacks (const std::vector<Controller::ScrollCallback>& scrollCallbacks) {

    m_scrollCallbacks = scrollCallbacks;

}

void Controller::addScrollCallback (const Controller::ScrollCallback& scrollCallback) {

    m_scrollCallbacks.push_back(scrollCallback);

}

void Controller::clearScrollCallbacks () {

    m_scrollCallbacks = {};

}

std::vector<Controller::ResizeCallback> Controller::getResizeCallbacks () {

    return m_resizeCallbacks;

}

void Controller::setResizeCallbacks (const std::vector<Controller::ResizeCallback>& resizeCallbacks) {

    m_resizeCallbacks = resizeCallbacks;

}

void Controller::addResizeCallback (const Controller::ResizeCallback& resizeCallback) {

    m_resizeCallbacks.push_back(resizeCallback);

}

void Controller::clearResizeCallbacks () {

    m_resizeCallbacks = {};

}
