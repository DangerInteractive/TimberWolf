#include "Controller.hpp"

Controller::Controller () {}

void Controller::onKey (int action, int mod, int key, int scanCode) {

    for (int i = 0; i < m_keybindings.size(); ++i) {
        m_keybindings[i].process(action, mod, key, scanCode);
    }

}

void Controller::onCursor (double xPos, double yPos) {

    std::ostringstream oss;
    oss << "Mouse " << xPos << " " << yPos;
    Log::verbose(oss.str());

}

void Controller::onCursorIn () {

    Log::verbose("Mouse In");

}

void Controller::onCursorOut () {

    Log::verbose("Mouse Out");

}

void Controller::onMouseButton (int action, int mod, int button) {

    std::ostringstream oss;
    oss << "Mouse Button " << action << " " << mod << " " << button;
    Log::verbose(oss.str());

}

void Controller::onScroll (double xOffset, double yOffset) {

    std::ostringstream oss;
    oss << "Scroll " << xOffset << " " << yOffset;
    Log::verbose(oss.str());

}

void Controller::onDrop (int count, const char** paths) {

    std::ostringstream oss;
    oss << "Drop " << count << " " << *paths;
    Log::verbose(oss.str());

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

void Controller::clearKeybindings () {

    m_keybindings = std::vector<Keybinding>();

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

void Controller::setKeybindings (std::vector<Keybinding> keybindings) {

    m_keybindings = keybindings;

}

void Controller::addKeybinding (Keybinding keybinding) {

    m_keybindings.push_back(keybinding);

}
