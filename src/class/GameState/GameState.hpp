#ifndef H_CLASS_GameState
#define H_CLASS_GameState

#include "../Controller/Controller.hpp"
class GameStateManager;

class GameState {

public:

    // GameState stacking transparency flags
    static const bool transparentRender = false;
    static const bool transparentUpdate = false;
    static const bool transparentInput = false;

    // constructor and destructor
    GameState () = default;
    virtual ~GameState () = default;

    GameState (GameState&&) = default;
    GameState& operator = (GameState&&) = default;

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
    virtual void render (float) = 0;
    virtual void update () = 0;

    // input handling
    Controller& getController ();
    void setController (Controller&);
    void clearController ();

protected:

    Controller m_controller;

};

#endif
