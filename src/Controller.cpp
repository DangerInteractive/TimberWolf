#include "../include/Controller.hpp"

tw::Controller::Controller () {}

void tw::Controller::onKey (int action, int mod, int key, int scanCode) {

    for (int i = 0; i < m_keybindings.size(); ++i) {
        m_keybindings[i].process(action, mod, key, scanCode);
    }
    Log::verbose("input", "Key ", action, " ", mod, " ", key, " ", scanCode);

}

void tw::Controller::onCursor (double xPos, double yPos) {

    Log::verbose("input", "Mouse ", xPos, " ", yPos);

}

void tw::Controller::onCursorIn () {

    Log::verbose("input", "Mouse In");

}

void tw::Controller::onCursorOut () {

    Log::verbose("input", "Mouse Out");

}

void tw::Controller::onMouseButton (int action, int mod, int button) {

    Log::verbose("input", "Mouse Button ", action, " ", mod, " ", button);

}

void tw::Controller::onScroll (double xOffset, double yOffset) {

    Log::verbose("input", "Scroll ", xOffset, " ", yOffset);

}

void tw::Controller::onDrop (int count, const char** paths) {

    Log::verbose("input", "Drop ", count, " ", *paths);

}

std::vector<tw::Keybinding> tw::Controller::getKeybindings () {

    return m_keybindings;

}

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

std::vector<tw::Keybinding> tw::Controller::getKeybindingsByKeyAction (KeyAction action) {

    std::vector<Keybinding> out;

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (action == m_keybindings[i].getAction()) {
            out.push_back(m_keybindings[i]);
        }

    }

    return out;

}

std::vector<tw::Keybinding> tw::Controller::getKeybindingsByKeyType (KeyType key) {

    std::vector<Keybinding> out;

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (key == m_keybindings[i].getKey()) {
            out.push_back(m_keybindings[i]);
        }

    }

    return out;

}

std::vector<tw::Keybinding> tw::Controller::getKeybindingsByKeyMod (KeyMod mod) {

    std::vector<Keybinding> out;

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (mod == m_keybindings[i].getMod()) {
            out.push_back(m_keybindings[i]);
        }

    }

    return out;

}

std::vector<tw::Keybinding> tw::Controller::getKeybindingsByScanCode (int scanCode) {

    std::vector<Keybinding> out;

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (scanCode == m_keybindings[i].getScanCode()) {
            out.push_back(m_keybindings[i]);
        }

    }

    return out;

}

void tw::Controller::setKeybindings (const std::vector<Keybinding>& keybindings) {

    m_keybindings = keybindings;

}

void tw::Controller::addKeybinding (const Keybinding& keybinding) {

    m_keybindings.push_back(keybinding);

}

void tw::Controller::clearKeybindings () {

    m_keybindings = {};

}

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

void tw::Controller::removeKeybindingsByKeyAction (KeyAction action) {

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (action == m_keybindings[i].getAction()) {
            m_keybindings.erase(m_keybindings.begin() + i);
            --i;
        }

    }

}

void tw::Controller::removeKeybindingsByKeyType (KeyType key) {

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (key == m_keybindings[i].getKey()) {
            m_keybindings.erase(m_keybindings.begin() + i);
            --i;
        }

    }

}

void tw::Controller::removeKeybindingsByKeyMod (KeyMod mod) {

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (mod == m_keybindings[i].getMod()) {
            m_keybindings.erase(m_keybindings.begin() + i);
            --i;
        }

    }

}

void tw::Controller::removeKeybindingsByScanCode (int scanCode) {

    for (int i = 0; i < m_keybindings.size(); ++i) {

        if (scanCode == m_keybindings[i].getScanCode()) {
            m_keybindings.erase(m_keybindings.begin() + i);
            --i;
        }

    }

}

std::vector<tw::Controller::CursorCallback> tw::Controller::getCursorCallbacks () {

    return m_cursorCallbacks;

}

void tw::Controller::setCursorCallbacks (const std::vector<Controller::CursorCallback>& cursorCallbacks) {

    m_cursorCallbacks = cursorCallbacks;

}

void tw::Controller::addCursorCallback (const Controller::CursorCallback& cursorCallback) {

    m_cursorCallbacks.push_back(cursorCallback);

}

void tw::Controller::clearCursorCallbacks () {

    m_cursorCallbacks = {};

}

std::vector<tw::Controller::CursorInCallback> tw::Controller::getCursorInCallbacks () {

    return m_cursorInCallbacks;

}

void tw::Controller::setCursorInCallbacks (const std::vector<Controller::CursorInCallback>& cursorInCallbacks) {

    m_cursorInCallbacks = cursorInCallbacks;

}

void tw::Controller::addCursorInCallback (const Controller::CursorInCallback& cursorInCallback) {

    m_cursorInCallbacks.push_back(cursorInCallback);

}

void tw::Controller::clearCursorInCallbacks () {

    m_cursorInCallbacks = {};

}

std::vector<tw::Controller::CursorOutCallback> tw::Controller::getCursorOutCallbacks () {

    return m_cursorOutCallbacks;

}

void tw::Controller::setCursorOutCallbacks (const std::vector<Controller::CursorOutCallback>& cursorOutCallbacks) {

    m_cursorOutCallbacks = cursorOutCallbacks;

}

void tw::Controller::addCursorOutCallback (const Controller::CursorOutCallback& cursorOutCallback) {

    m_cursorOutCallbacks.push_back(cursorOutCallback);

}

void tw::Controller::clearCursorOutCallbacks () {

    m_cursorOutCallbacks = {};

}

std::vector<tw::Controller::FocusCallback> tw::Controller::getFocusCallbacks () {

    return m_focusCallbacks;

}

void tw::Controller::setFocusCallbacks (const std::vector<Controller::FocusCallback>& focusCallbacks) {

    m_focusCallbacks = focusCallbacks;

}

void tw::Controller::addFocusCallback (const Controller::FocusCallback& focusCallback) {

    m_focusCallbacks.push_back(focusCallback);

}

void tw::Controller::clearFocusCallbacks () {

    m_focusCallbacks = {};

}

std::vector<tw::Controller::UnfocusCallback> tw::Controller::getUnfocusCallbacks () {

    return m_unfocusCallbacks;

}

void tw::Controller::setUnfocusCallbacks (const std::vector<Controller::UnfocusCallback>& unfocusCallbacks) {

    m_unfocusCallbacks = unfocusCallbacks;

}

void tw::Controller::addUnfocusCallback (const Controller::UnfocusCallback& unfocusCallback) {

    m_unfocusCallbacks.push_back(unfocusCallback);

}

void tw::Controller::clearUnfocusCallbacks () {

    m_unfocusCallbacks = {};

}

std::vector<tw::Controller::MouseButtonPressCallback> tw::Controller::getMouseButtonPressCallbacks () {

    return m_mouseButtonPressCallbacks;

}

void tw::Controller::setMouseButtonPressCallbacks (const std::vector<Controller::MouseButtonPressCallback>& mouseButtonPressCallbacks) {

    m_mouseButtonPressCallbacks = mouseButtonPressCallbacks;

}

void tw::Controller::addMouseButtonPressCallback (const Controller::MouseButtonPressCallback& mouseButtonPressCallback) {

    m_mouseButtonPressCallbacks.push_back(mouseButtonPressCallback);

}

void tw::Controller::clearMouseButtonPressCallbacks () {

    m_mouseButtonPressCallbacks = {};

}

std::vector<tw::Controller::MouseButtonReleaseCallback> tw::Controller::getMouseButtonReleaseCallbacks () {

    return m_mouseButtonReleaseCallbacks;

}

void tw::Controller::setMouseButtonReleaseCallbacks (const std::vector<Controller::MouseButtonReleaseCallback>& mouseButtonReleaseCallbacks) {

    m_mouseButtonReleaseCallbacks = mouseButtonReleaseCallbacks;

}

void tw::Controller::addMouseButtonReleaseCallback (const MouseButtonReleaseCallback& mouseButtonReleaseCallback) {

    m_mouseButtonReleaseCallbacks.push_back(mouseButtonReleaseCallback);

}

void tw::Controller::clearMouseButtonReleaseCallbacks () {

    m_mouseButtonReleaseCallbacks = {};

}

std::vector<tw::Controller::ScrollCallback> tw::Controller::getScrollCallbacks () {

    return m_scrollCallbacks;

}

void tw::Controller::setScrollCallbacks (const std::vector<ScrollCallback>& scrollCallbacks) {

    m_scrollCallbacks = scrollCallbacks;

}

void tw::Controller::addScrollCallback (const ScrollCallback& scrollCallback) {

    m_scrollCallbacks.push_back(scrollCallback);

}

void tw::Controller::clearScrollCallbacks () {

    m_scrollCallbacks = {};

}

std::vector<tw::Controller::ResizeCallback> tw::Controller::getResizeCallbacks () {

    return m_resizeCallbacks;

}

void tw::Controller::setResizeCallbacks (const std::vector<ResizeCallback>& resizeCallbacks) {

    m_resizeCallbacks = resizeCallbacks;

}

void tw::Controller::addResizeCallback (const ResizeCallback& resizeCallback) {

    m_resizeCallbacks.push_back(resizeCallback);

}

void tw::Controller::clearResizeCallbacks () {

    m_resizeCallbacks = {};

}
