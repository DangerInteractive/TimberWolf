#ifndef H_TW_CONTROLLER
#define H_TW_CONTROLLER

/**
 * @file
 *
 * Header file for the tw::Controller class.
 */

#include <vector>
#include <sstream>
#include <functional>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Log/Log.hpp"
#include "KeyAction.hpp"
#include "KeyType.hpp"
#include "Keybinding.hpp"

namespace tw {
class Controller {

public:

    typedef std::function <void (double, double)> CursorCallback;
    typedef std::function <void ()> CursorInCallback;
    typedef std::function <void ()> CursorOutCallback;
    typedef std::function <void ()> FocusCallback;
    typedef std::function <void ()> UnfocusCallback;
    typedef std::function <void (int, int)> MouseButtonPressCallback;
    typedef std::function <void (int, int)> MouseButtonReleaseCallback;
    typedef std::function <void (double, double)> ScrollCallback;
    typedef std::function <void (int, int)> ResizeCallback;

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
    void setKeybindings (const std::vector<Keybinding>&);
    void addKeybinding (const Keybinding&);
    void clearKeybindings ();
    void removeKeybindings (KeyAction, KeyMod, KeyType, int = 0);
    void removeKeybindingsByKeyAction (KeyAction);
    void removeKeybindingsByKeyType (KeyType);
    void removeKeybindingsByKeyMod (KeyMod);
    void removeKeybindingsByScanCode (int);

    std::vector<CursorCallback> getCursorCallbacks ();
    void setCursorCallbacks (const std::vector<CursorCallback>&);
    void addCursorCallback (const CursorCallback&);
    void clearCursorCallbacks ();

    std::vector<CursorInCallback> getCursorInCallbacks ();
    void setCursorInCallbacks (const std::vector<CursorInCallback>&);
    void addCursorInCallback (const CursorInCallback&);
    void clearCursorInCallbacks ();

    std::vector<CursorOutCallback> getCursorOutCallbacks ();
    void setCursorOutCallbacks (const std::vector<CursorOutCallback>&);
    void addCursorOutCallback (const CursorOutCallback&);
    void clearCursorOutCallbacks ();

    std::vector<FocusCallback> getFocusCallbacks ();
    void setFocusCallbacks (const std::vector<FocusCallback>&);
    void addFocusCallback (const FocusCallback&);
    void clearFocusCallbacks ();

    std::vector<UnfocusCallback> getUnfocusCallbacks ();
    void setUnfocusCallbacks (const std::vector<UnfocusCallback>&);
    void addUnfocusCallback (const UnfocusCallback&);
    void clearUnfocusCallbacks ();

    std::vector<MouseButtonPressCallback> getMouseButtonPressCallbacks ();
    void setMouseButtonPressCallbacks (const std::vector<MouseButtonPressCallback>&);
    void addMouseButtonPressCallback (const MouseButtonPressCallback&);
    void clearMouseButtonPressCallbacks ();

    std::vector<MouseButtonReleaseCallback> getMouseButtonReleaseCallbacks ();
    void setMouseButtonReleaseCallbacks (const std::vector<MouseButtonReleaseCallback>&);
    void addMouseButtonReleaseCallback (const MouseButtonReleaseCallback&);
    void clearMouseButtonReleaseCallbacks ();

    std::vector<ScrollCallback> getScrollCallbacks ();
    void setScrollCallbacks (const std::vector<ScrollCallback>&);
    void addScrollCallback (const ScrollCallback&);
    void clearScrollCallbacks ();

    std::vector<ResizeCallback> getResizeCallbacks ();
    void setResizeCallbacks (const std::vector<ResizeCallback>&);
    void addResizeCallback (const ResizeCallback&);
    void clearResizeCallbacks ();

private:

    std::vector<Keybinding> m_keybindings;

    std::vector<CursorCallback> m_cursorCallbacks;
    std::vector<CursorInCallback> m_cursorInCallbacks;
    std::vector<CursorOutCallback> m_cursorOutCallbacks;
    std::vector<FocusCallback> m_focusCallbacks;
    std::vector<UnfocusCallback> m_unfocusCallbacks;
    std::vector<MouseButtonPressCallback> m_mouseButtonPressCallbacks;
    std::vector<MouseButtonReleaseCallback> m_mouseButtonReleaseCallbacks;
    std::vector<ScrollCallback> m_scrollCallbacks;
    std::vector<ResizeCallback> m_resizeCallbacks;

};
}

#endif
