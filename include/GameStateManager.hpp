#ifndef H_TW_STATEMANAGER
#define H_TW_STATEMANAGER

#include <vector>
#include <memory>
#include <mutex>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Controller.hpp"
#include "GameState.hpp"
#include "GameStateStore.hpp"
#include "Window.hpp"
#include "Log.hpp"

namespace tw {
class GameStateManager {

public:

    GameStateManager () = delete; // static only
    ~GameStateManager () = delete;

    GameStateManager (GameStateManager&&) = delete;
    GameStateManager& operator = (GameStateManager&&) = delete;

    GameStateManager (const GameStateManager&) = delete;
    GameStateManager& operator = (const GameStateManager&) = delete;

    template <typename TState, typename ...TArg>
    static std::shared_ptr<GameState> pushNewState (TArg&&... args) {
        auto state = std::make_shared<TState>(std::forward<TArg>(args)...);
        pushState(state);
        return state;
    }
    static void pushState (const std::shared_ptr<GameState>&);
    static void pushState (GameState*);
    static bool pushState (const std::string&);
    static void dropState ();
    static std::shared_ptr<GameState> popState ();

    static void refreshLiveStates ();

    static void clearWindow ();
    static void render (double);

    static void update (double);

    static void keyCallback (GLFWwindow*, int, int, int, int = -1);
    static void cursorCallback (GLFWwindow*, double, double);
    static void cursorInOutCallback (GLFWwindow*, int);
    static void mouseButtonCallback (GLFWwindow*, int, int, int);
    static void scrollCallback (GLFWwindow*, double, double);
    static void dropCallback (GLFWwindow*, int, const char**);

private:

    static std::vector<std::shared_ptr<GameState>> m_states;

    static std::vector<std::shared_ptr<GameState>> m_statesLiveRender;
    static std::vector<std::shared_ptr<GameState>> m_statesLiveUpdate;
    static std::vector<std::shared_ptr<GameState>> m_statesLiveInput;

};
}

#endif
