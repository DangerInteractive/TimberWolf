#include "../include/KeyMod.hpp"

tw::KeyMod::KeyMod (int flags)
: m_flags(flags) {}

tw::KeyMod::KeyMod (bool shift, bool ctrl, bool alt, bool super)
: m_flags(shift | ctrl | alt | super) {}

int tw::KeyMod::getFlags () const {

    return m_flags;

}

bool tw::KeyMod::getShift () const {

    return (KeyMod::MOD_SHIFT & m_flags) == KeyMod::MOD_SHIFT;

}

bool tw::KeyMod::getControl () const {

    return (KeyMod::MOD_CONTROL & m_flags) == KeyMod::MOD_CONTROL;

}

bool tw::KeyMod::getAlt () const {

    return (KeyMod::MOD_ALT & m_flags) == KeyMod::MOD_ALT;

}

bool tw::KeyMod::getSuper () const {

    return (KeyMod::MOD_SUPER & m_flags) == KeyMod::MOD_SUPER;

}

void tw::KeyMod::setFlags (int flags) {

    m_flags = 0x0000000f & flags;

}

void tw::KeyMod::setShift (bool shift) {

    if (shift) {
        m_flags = KeyMod::MOD_SHIFT | m_flags;
    } else {
        m_flags = ~KeyMod::MOD_SHIFT & m_flags;
    }

}

void tw::KeyMod::setControl (bool control) {

    if (control) {
        m_flags = KeyMod::MOD_CONTROL | m_flags;
    } else {
        m_flags = ~KeyMod::MOD_CONTROL & m_flags;
    }

}

void tw::KeyMod::setAlt (bool alt) {

    if (alt) {
        m_flags = KeyMod::MOD_ALT | m_flags;
    } else {
        m_flags = ~KeyMod::MOD_ALT & m_flags;
    }

}

void tw::KeyMod::setSuper (bool super) {

    if (super) {
        m_flags = KeyMod::MOD_SUPER | m_flags;
    } else {
        m_flags = ~KeyMod::MOD_SUPER & m_flags;
    }

}

bool tw::KeyMod::operator == (const KeyMod right) {

    return getFlags() == right.getFlags();

}

bool tw::KeyMod::operator != (const KeyMod right) {

    return getFlags() != right.getFlags();

}
