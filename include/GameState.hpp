#ifndef H_CLASS_GameState
#define H_CLASS_GameState

#include "Controller.hpp"
#include "Window.hpp"
#include "Color.hpp"
namespace tw { class GameStateManager; }

namespace tw {
class GameState {

public:

    // GameState stacking transparency flags
    static const bool transparentRender = false;
    static const bool transparentUpdate = false;
    static const bool transparentInput = false;

    // constructor and destructor
    GameState () = default;
    virtual ~GameState () = default;

    // move operations
    GameState (GameState&&) = default;
    GameState& operator = (GameState&&) = default;

    // copy operations
    GameState (const GameState&) = default;
    GameState& operator = (const GameState&) = default;

    // state management event callbacks
    virtual void onActivate () = 0;
    virtual void onDeactivate () = 0;
    virtual void onPush () = 0;
    virtual void onPop () = 0;
    virtual void onAscend () = 0;
    virtual void onDescend () = 0;

    // game loop callbacks
    void clearWindow ();
    virtual void render (double) = 0;
    virtual void update (double) = 0;

    // input handling
    Controller& getController ();
    void setController (Controller&&);
    void setController (Controller&);
    void clearController ();

protected:

    Controller m_controller;
    bool m_clearWindow {false};
    Color m_clearColor {0.f, 0.f, 0.f, 1.f};

};
}

#endif
