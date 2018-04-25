#ifndef H_TW_KEYBINDING
#define H_TW_KEYBINDING

#include <vector>
#include <functional>
#include "KeyMod.hpp"
#include "KeyAction.hpp"
#include "KeyType.hpp"

namespace tw {
class Keybinding {

public:

    typedef std::function <void ()> KeybindingCallback;

    Keybinding (KeybindingCallback, KeyAction, const KeyMod&, KeyType, int = -1);
    Keybinding (KeybindingCallback, KeyAction, unsigned int, KeyType, int = -1);
    ~Keybinding () = default;

    Keybinding (Keybinding&&) = default;
    Keybinding& operator = (Keybinding&&) = default;

    Keybinding (const Keybinding&) = default;
    Keybinding& operator = (const Keybinding&) = default;

    bool check (int, int, int, int = -1) const;
    void process (int, int, int, int = -1);

    const KeybindingCallback& getCallback () const;
    KeyAction getAction () const;
    const KeyMod& getMod () const;
    bool getAlt () const;
    bool getControl () const;
    bool getShift () const;
    bool getSuper () const;
    KeyType getKey () const;
    int getScanCode () const;

    void setCallback (const KeybindingCallback&);
    void setAction (KeyAction);
    void setMod (const KeyMod&);
    void setMod (unsigned int);
    void setAlt (bool);
    void setControl (bool);
    void setShift (bool);
    void setSuper (bool);
    void setKey (KeyType);
    void setScanCode (int);

private:

    KeybindingCallback m_callback;
    KeyAction m_action;
    KeyMod m_mod;
    KeyType m_key;
    int m_scanCode;

};
}

#endif
