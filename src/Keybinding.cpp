#include "../include/Keybinding.hpp"

/**
 * @class tw::Keybinding
 *
 * Representation of a keyboard keybinding, to be stored in a tw::Controller
 * object.
 */

tw::Keybinding::Keybinding (
    KeybindingCallback callback,
    KeyAction action,
    const KeyMod& mod,
    KeyType key,
    int scanCode
)
: m_callback(callback), m_action(action), m_mod(mod), m_key(key), m_scanCode(scanCode) {}

tw::Keybinding::Keybinding (
    KeybindingCallback callback,
    KeyAction action,
    unsigned int mod,
    KeyType key,
    int scanCode
)
: Keybinding(callback, action, KeyMod(mod), key, scanCode) {}

bool tw::Keybinding::check (int action, int mod, int key, int scanCode) const {

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

const tw::Keybinding::KeybindingCallback& tw::Keybinding::getCallback () const {

    return m_callback;

}

tw::KeyAction tw::Keybinding::getAction () const {

    return m_action;

}

const tw::KeyMod& tw::Keybinding::getMod () const {

    return m_mod;

}

bool tw::Keybinding::getAlt () const {

    return m_mod.getAlt();

}

bool tw::Keybinding::getControl () const {

    return m_mod.getControl();

}

bool tw::Keybinding::getShift () const {

    return m_mod.getShift();

}

bool tw::Keybinding::getSuper () const {

    return m_mod.getSuper();

}

tw::KeyType tw::Keybinding::getKey () const {

    return m_key;

}

int tw::Keybinding::getScanCode () const {

    return m_scanCode;

}

void tw::Keybinding::setCallback (const KeybindingCallback& callback) {

    m_callback = callback;

}

void tw::Keybinding::setAction (KeyAction action) {

    m_action = action;

}

void tw::Keybinding::setMod (const KeyMod& mod) {

    m_mod = mod;

}

void tw::Keybinding::setMod (unsigned int mod) {

    m_mod = KeyMod(mod);

}

void tw::Keybinding::setAlt (bool alt) {

    m_mod.setAlt(alt);

}

void tw::Keybinding::setControl (bool control) {

    m_mod.setControl(control);

}

void tw::Keybinding::setShift (bool shift) {

    m_mod.setShift(shift);

}

void tw::Keybinding::setSuper (bool super) {

    m_mod.setSuper(super);

}

void tw::Keybinding::setKey (KeyType key) {

    m_key = key;

}

void tw::Keybinding::setScanCode (int scanCode) {

    m_scanCode = scanCode;

}
