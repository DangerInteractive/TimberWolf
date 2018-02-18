#include "KeyMod.hpp"

KeyMod::KeyMod (int flags)
: m_flags(flags)
{}

KeyMod::KeyMod (bool shift, bool ctrl, bool alt, bool super)
: m_flags(shift | ctrl | alt | super)
{}

int KeyMod::getFlags () const {

    return m_flags;

}

bool KeyMod::getShift () const {

    return (KeyMod::MOD_SHIFT & m_flags) == KeyMod::MOD_SHIFT;

}

bool KeyMod::getControl () const {

    return (KeyMod::MOD_CONTROL & m_flags) == KeyMod::MOD_CONTROL;

}

bool KeyMod::getAlt () const {

    return (KeyMod::MOD_ALT & m_flags) == KeyMod::MOD_ALT;

}

bool KeyMod::getSuper () const {

    return (KeyMod::MOD_SUPER & m_flags) == KeyMod::MOD_SUPER;

}

void KeyMod::setFlags (int flags) {

    m_flags = 0x0000000f & flags;

}

void KeyMod::setShift (bool shift) {

    if (shift) {
        m_flags = KeyMod::MOD_SHIFT | m_flags;
    } else {
        m_flags = ~KeyMod::MOD_SHIFT & m_flags;
    }

}

void KeyMod::setControl (bool control) {

    if (control) {
        m_flags = KeyMod::MOD_CONTROL | m_flags;
    } else {
        m_flags = ~KeyMod::MOD_CONTROL & m_flags;
    }

}

void KeyMod::setAlt (bool alt) {

    if (alt) {
        m_flags = KeyMod::MOD_ALT | m_flags;
    } else {
        m_flags = ~KeyMod::MOD_ALT & m_flags;
    }

}

void KeyMod::setSuper (bool super) {

    if (super) {
        m_flags = KeyMod::MOD_SUPER | m_flags;
    } else {
        m_flags = ~KeyMod::MOD_SUPER & m_flags;
    }

}

bool KeyMod::operator == (const KeyMod right) {

    return getFlags() == right.getFlags();

}

bool KeyMod::operator != (const KeyMod right) {

    return getFlags() != right.getFlags();

}
