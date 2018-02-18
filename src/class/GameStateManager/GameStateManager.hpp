#ifndef H_CLASS_STATEMANAGER
#define H_CLASS_STATEMANAGER

#include <vector>
#include <memory>
#include <mutex>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Controller/Controller.hpp"
#include "../GameState/GameState.hpp"
#include "../GameStateStore/GameStateStore.hpp"
#include "../Window/Window.hpp"
#include "../Log/Log.hpp"

class GameStateManager {

public:

    GameStateManager () = delete; // static only
    ~GameStateManager () = delete;

    GameStateManager (GameStateManager&&) = delete;
    GameStateManager& operator = (GameStateManager&&) = delete;

    GameStateManager (const GameStateManager&) = delete;
    GameStateManager& operator = (const GameStateManager&) = delete;

    static void pushState (GameState*);
    static bool pushState (std::string);
    static void dropState ();
    static GameState* popState ();

    static void refreshLiveStates ();

    static void render (double);

    static void update ();

    static void keyCallback (GLFWwindow*, int, int, int, int = -1);
    static void cursorCallback (GLFWwindow*, double, double);
    static void cursorInOutCallback (GLFWwindow*, int);
    static void mouseButtonCallback (GLFWwindow*, int, int, int);
    static void scrollCallback (GLFWwindow*, double, double);
    static void dropCallback (GLFWwindow*, int, const char**);

private:

    static std::vector<GameState*> m_states;

    static std::vector<GameState*> m_statesLiveRender;
    static std::vector<GameState*> m_statesLiveUpdate;
    static std::vector<GameState*> m_statesLiveInput;

};

#endif
