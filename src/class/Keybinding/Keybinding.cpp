#include "Keybinding.hpp"

tw::Keybinding::Keybinding (
    KeybindingCallback callback,
    KeyAction action,
    KeyMod mod,
    KeyType key,
    int scanCode
) :
  m_callback(callback),
  m_action(action),
  m_mod(mod),
  m_key(key),
  m_scanCode(scanCode)
{}

bool tw::Keybinding::check (int action, int mod, int key, int scanCode) {

    if (
        key == KeyType::NONE ||
        (
            action == m_action &&
            mod == m_mod.getFlags() &&
            key == m_key
        ) ||
        (
            key == KeyType::UNKNOWN &&
            scanCode == m_scanCode
        )
    ) {
        return true;
    } else {
        return false;
    }

}

void tw::Keybinding::process (int action, int mod, int key, int scanCode) {

    if (check(action, mod, key, scanCode)) {
        m_callback();
    }

}
