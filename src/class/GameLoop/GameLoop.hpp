#ifndef H_CLASS_GAMELOOP
#define H_CLASS_GAMELOOP

#include <chrono>
#include <thread>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Log/Log.hpp"
#include "../GameStateManager/GameStateManager.hpp"
#include "../Window/Window.hpp"

class GameLoop {

public:

    GameLoop () = delete; // static only
    ~GameLoop () = delete;

    GameLoop (GameLoop&&) = delete;
    GameLoop& operator = (GameLoop&&) = delete;

    GameLoop (const GameLoop&) = delete;
    GameLoop& operator = (const GameLoop&) = delete;

    static void setRenderFrameRate (int);
    static void setUpdateTickRate (int);

    static void run ();
    static void freeze ();
    static bool isRunning ();

private:

    static void update (int&, double&, bool&, bool&, bool&);

    static void render (double);
    static void input ();

    static int m_renderFrameRate;
    static int m_updateTickRate;

    static double m_renderSeconds;
    static double m_updateSeconds;

    static bool m_windowOpen;
    static bool m_isRunning;

    static bool m_renderLoopRunning;
    static bool m_updateLoopRunning;

    static std::thread m_updateThread;

};

#endif
