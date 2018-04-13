#ifndef H_CLASS_KEYBINDING
#define H_CLASS_KEYBINDING

#include <vector>
#include "../KeyMod/KeyMod.hpp"
#include "../../enum/KeyAction/KeyAction.hpp"
#include "../../enum/KeyType/KeyType.hpp"

namespace tw {
class Keybinding {

public:

    typedef void (* KeybindingCallback) ();

    Keybinding (KeybindingCallback, KeyAction, KeyMod, KeyType, int = -1);
    ~Keybinding () = default;

    Keybinding (Keybinding&&) = default;
    Keybinding& operator = (Keybinding&&) = default;

    Keybinding (const Keybinding&) = default;
    Keybinding& operator = (const Keybinding&) = default;

    bool check (int, int, int, int = -1);
    void process (int, int, int, int = -1);

    KeybindingCallback m_callback;
    KeyAction m_action;
    KeyMod m_mod;
    KeyType m_key;
    int m_scanCode;

};
}

#endif
