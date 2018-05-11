#include "../include/Keybinding.hpp"

/**
 * @class tw::Keybinding
 *
 * Representation of a keyboard keybinding, to be stored in a tw::Controller
 * object.
 */

/**
 * Constructor taking in a callback function, the desired action (release,
 * press, or hold), the key modifier (which extra keys should be held), the key
 * type (game engine key code), and optionally an OS key scan code.
 *
 * @param callback callback function
 * @param action   0 for release, 1 for press, 2 for hold
 * @param mod      key modifier via tw::KeyMod
 * @param key      engine key code
 * @param scanCode OS key scan code
 */
tw::Keybinding::Keybinding (
    KeybindingCallback callback,
    KeyAction action,
    const KeyMod& mod,
    KeyType key,
    int scanCode
)
: m_callback(callback), m_action(action), m_mod(mod), m_key(key), m_scanCode(scanCode) {}

/**
 * Constructor taking in a callback function, the desired action (release,
 * press, or hold), the key modifier (which extra keys should be held), the key
 * type (game engine key code), and optionally an OS key scan code.
 *
 * @param callback callback function
 * @param action   0 for release, 1 for press, 2 for hold
 * @param mod      key modifier via bitmask
 * @param key      engine key code
 * @param scanCode OS key scan code
 */
tw::Keybinding::Keybinding (
    KeybindingCallback callback,
    KeyAction action,
    unsigned int mod,
    KeyType key,
    int scanCode
)
: Keybinding(callback, action, KeyMod(mod), key, scanCode) {}

/**
 * Check if a given set of key input parameters match the keybinding. This does
 * not actually call the callback.
 *
 * @param action   0 for release, 1 for press, 2 for hold
 * @param mod      key modifier
 * @param key      engine key code
 * @param scanCode OS key scan code
 * @return true if the parameters match the keybinding, false if not
 */
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

/**
 * Process the parameters of a key input event, and if it matches the
 * keybinding, execute the callback function. This should be called by the game
 * state that it belongs to.
 *
 * @param action   0 for release, 1 for press, 2 for hold
 * @param mod      key modifier
 * @param key      engine key code
 * @param scanCode OS key scan code
 */
void tw::Keybinding::process (int action, int mod, int key, int scanCode) {

    if (check(action, mod, key, scanCode)) {
        m_callback();
    }

}

/**
 * Get the callback function.
 *
 * @return callback function
 */
const tw::Keybinding::KeybindingCallback& tw::Keybinding::getCallback () const {

    return m_callback;

}

/**
 * Get the key action value (release, press, or hold).
 *
 * @return 0 for release, 1 for press, 2 for hold
 */
tw::KeyAction tw::Keybinding::getAction () const {

    return m_action;

}

/**
 * Get the key modifier (which extra keys are to be held) as a tw::KeyMod.
 *
 * @return key modifier
 */
const tw::KeyMod& tw::Keybinding::getMod () const {

    return m_mod;

}

/**
 * Check if the alt key is in the modifier.
 *
 * @return true if alt key is in the modifier, false if not
 */
bool tw::Keybinding::getAlt () const {

    return m_mod.getAlt();

}

/**
 * Check if the control key is in the modifier.
 *
 * @return true if control key is in the modifier, false if not
 */
bool tw::Keybinding::getControl () const {

    return m_mod.getControl();

}

/**
 * Check if the shift key is in the modifier.
 *
 * @return true if shift key is in the modifier, false if not
 */
bool tw::Keybinding::getShift () const {

    return m_mod.getShift();

}

/**
 * Check if the super key is in the modifier.
 *
 * @return true if super key is in the modifier, false if not
 */
bool tw::Keybinding::getSuper () const {

    return m_mod.getSuper();

}

/**
 * Get the engine key code.
 *
 * @return engine key code
 */
tw::KeyType tw::Keybinding::getKey () const {

    return m_key;

}

/**
 * Get the OS key scan code.
 *
 * @return OS key scan code
 */
int tw::Keybinding::getScanCode () const {

    return m_scanCode;

}

/**
 * Set callback function.
 *
 * @param callback callback function
 */
void tw::Keybinding::setCallback (const KeybindingCallback& callback) {

    m_callback = callback;

}

/**
 * Set the key action (whether its a release, press, or hold binding).
 *
 * @param action 0 for release, 1 for press, 2 for hold
 */
void tw::Keybinding::setAction (KeyAction action) {

    m_action = action;

}

/**
 * Set the key modifier (which extra keys are to be held during the key event,
 * including alt, control, shift, and super) via tw::KeyMod.
 *
 * @param mod key modifier
 */
void tw::Keybinding::setMod (const KeyMod& mod) {

    m_mod = mod;

}

/**
 * Set the key modifier (which extra keys are to be held during the key event,
 * including alt, control, shift, and super) via bitmask.
 *
 * @param mod key modifier
 */
void tw::Keybinding::setMod (unsigned int mod) {

    m_mod = KeyMod(mod);

}

/**
 * Set whether or not the key modifier contains the alt key.
 *
 * @param alt true to enable alt, false to disable
 */
void tw::Keybinding::setAlt (bool alt) {

    m_mod.setAlt(alt);

}

/**
 * Set whether or not the key modifier contains the control key.
 *
 * @param control true to enable control, false to disable
 */
void tw::Keybinding::setControl (bool control) {

    m_mod.setControl(control);

}

/**
 * Set whether or not the key modifier contains the shift key.
 *
 * @param shift true to enable shift, false to disable
 */
void tw::Keybinding::setShift (bool shift) {

    m_mod.setShift(shift);

}

/**
 * Set whether or not the key modifier contains the super key.
 *
 * @param super true to enable super, false to disable
 */
void tw::Keybinding::setSuper (bool super) {

    m_mod.setSuper(super);

}

/**
 * Set the game engine key code (see tw::KeyType).
 *
 * @param key engine key code
 */
void tw::Keybinding::setKey (KeyType key) {

    m_key = key;

}

/**
 * Set the OS key scan code. This is useful if the key you're trying to listen
 * for isn't present in the engine key code list. If it is, leave this alone.
 *
 * @param scanCode OS key scan code
 */
void tw::Keybinding::setScanCode (int scanCode) {

    m_scanCode = scanCode;

}
