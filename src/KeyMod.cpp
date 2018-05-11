#include "../include/KeyMod.hpp"

/**
 * @class tw::KeyMod
 *
 * Representation of a keybinding modificiation, which are additional keys being
 * held during a keypress, such as control in Ctrl+Z. Stores a bit for each of
 * shift, control, alt, and super keys.
 */

/**
 * Contructor taking in a bitmask.
 *
 * @param flags bitmask of enabled keys
 */
tw::KeyMod::KeyMod (int flags)
: m_flags(flags) {}

/**
 * Constructor taking in individual booleans for each key.
 *
 * @param shift true to enable shift, false to disable
 * @param ctrl  true to enable control, false to disable
 * @param alt   true to enable alt, false to disable
 * @param super true to enable super, false to disable
 */
tw::KeyMod::KeyMod (bool shift, bool ctrl, bool alt, bool super)
: m_flags(shift | ctrl | alt | super) {}

/**
 * Get all key flags as a bitmask.
 *
 * @return bitmask with all key flags
 */
int tw::KeyMod::getFlags () const {

    return m_flags;

}

/**
 * Check if shift key is enabled.
 *
 * @return true if shift is enabled, false if not
 */
bool tw::KeyMod::getShift () const {

    return m_flags & MOD_SHIFT;

}

/**
 * Check if control key is enabled.
 *
 * @return true if control is enabled, false if not
 */
bool tw::KeyMod::getControl () const {

    return m_flags & MOD_CONTROL;

}

/**
 * Check if alt key is enabled.
 *
 * @return true if alt is enabled, false if not
 */
bool tw::KeyMod::getAlt () const {

    return m_flags & MOD_ALT;

}

/**
 * Check if super key is enabled.
 *
 * @return true if super is enabled, false if not
 */
bool tw::KeyMod::getSuper () const {

    return m_flags & MOD_SUPER;

}

/**
 * Replace all existing set flags with a given bitmask.
 *
 * @param flags new bitmask of flags
 */
void tw::KeyMod::setFlags (int flags) {

    m_flags = flags;

}

/**
 * Set whether or not shift is enabled.
 *
 * @param shift true to enable shift, false to disable
 */
void tw::KeyMod::setShift (bool shift) {

    if (shift) {
        m_flags = MOD_SHIFT | m_flags;
    } else {
        m_flags = ~MOD_SHIFT & m_flags;
    }

}

/**
 * Set whether or not control is enabled.
 *
 * @param control true to enable control, false to disable
 */
void tw::KeyMod::setControl (bool control) {

    if (control) {
        m_flags = MOD_CONTROL | m_flags;
    } else {
        m_flags = ~MOD_CONTROL & m_flags;
    }

}

/**
 * Set whether or not alt is enabled.
 *
 * @param alt true to enable alt, false to disable
 */
void tw::KeyMod::setAlt (bool alt) {

    if (alt) {
        m_flags = MOD_ALT | m_flags;
    } else {
        m_flags = ~MOD_ALT & m_flags;
    }

}

/**
 * Set whether or not control is enabled.
 *
 * @param super true to enable super, false to disable
 */
void tw::KeyMod::setSuper (bool super) {

    if (super) {
        m_flags = MOD_SUPER | m_flags;
    } else {
        m_flags = ~MOD_SUPER & m_flags;
    }

}

/**
 * Check if two tw::KeyMod objects are equal.
 *
 * @return true if all flags are equal, false if not
 */
bool tw::KeyMod::operator == (const KeyMod& right) {

    return getFlags() == right.getFlags();

}

/**
 * Check if two tw::KeyMod objects are not equal.
 *
 * @return true if any flags are not equal, false if all are equal
 */
bool tw::KeyMod::operator != (const KeyMod& right) {

    return getFlags() != right.getFlags();

}
