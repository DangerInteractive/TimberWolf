#ifndef H_CLASS_CONTROLLER
#define H_CLASS_CONTROLLER

#include <vector>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Log/Log.hpp"
#include "../../enum/KeyAction/KeyAction.hpp"
#include "../../enum/KeyType/KeyType.hpp"
#include "../Keybinding/Keybinding.hpp"

class Controller {

public:

    Controller ();
    ~Controller () = default;

    Controller (Controller&&) = default;
    Controller& operator = (Controller&&) = default;

    Controller (const Controller&) = default;
    Controller& operator = (const Controller&) = default;

    void onKey (int, int, int, int = -1);
    void onCursor (double, double);
    void onCursorIn ();
    void onCursorOut ();
    void onMouseButton (int, int, int);
    void onScroll (double, double);
    void onDrop (int, const char**);

    std::vector<Keybinding> getKeybindings ();
    std::vector<Keybinding> getKeybindings (KeyAction, KeyMod, KeyType, int = 0);
    std::vector<Keybinding> getKeybindingsByKeyAction (KeyAction);
    std::vector<Keybinding> getKeybindingsByKeyType (KeyType);
    std::vector<Keybinding> getKeybindingsByKeyMod (KeyMod);
    std::vector<Keybinding> getKeybindingsByScanCode (int);

    void clearKeybindings ();
    void removeKeybindings (KeyAction, KeyMod, KeyType, int = 0);
    void removeKeybindingsByKeyAction (KeyAction);
    void removeKeybindingsByKeyType (KeyType);
    void removeKeybindingsByKeyMod (KeyMod);
    void removeKeybindingsByScanCode (int);

    void setKeybindings (std::vector<Keybinding>);
    void addKeybinding (Keybinding);

private:

    std::vector<Keybinding> m_keybindings;

};

#endif
