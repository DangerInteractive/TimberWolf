#ifndef H_CLASS_GAMELOOP
#define H_CLASS_GAMELOOP

#include <chrono>
#include <thread>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Log.hpp"
#include "GameStateManager.hpp"
#include "Window.hpp"
#include "Clock.hpp"

namespace tw {
class GameLoop {

public:

    GameLoop () = delete; // static only
    ~GameLoop () = delete;

    GameLoop (GameLoop&&) = delete;
    GameLoop& operator = (GameLoop&&) = delete;

    GameLoop (const GameLoop&) = delete;
    GameLoop& operator = (const GameLoop&) = delete;

    static unsigned int getRenderFrameRate ();
    static unsigned int getUpdateFrameRate ();

    static void setRenderFrameRate (unsigned int);
    static void setUpdateTickRate (unsigned int);

    static void run ();
    static void freeze ();
    static bool isRunning ();

private:

    static void update (Clock&, unsigned int&, double&, bool&, bool&, bool&);

    static void render (double);

    static unsigned int m_renderFrameRate;
    static unsigned int m_updateTickRate;

    static double m_renderSeconds;
    static double m_updateSeconds;

    static Clock m_renderLoopClock;
    static Clock m_updateLoopClock;

    static bool m_windowOpen;
    static bool m_isRunning;

    static bool m_renderLoopRunning;
    static bool m_updateLoopRunning;

    static std::thread m_updateThread;

};
}

#endif
