#ifndef H_TW_GAMELOOP
#define H_TW_GAMELOOP

/**
 * @file
 *
 * Header file for the tw::GameLoop class.
 */

#include <chrono>
#include <thread>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Log/Log.hpp"
#include "GameStateManager.hpp"
#include "../Window/Window.hpp"
#include "../Core/SpeedGovernor.hpp"

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
    static unsigned int getUpdateTickRate ();

    static double getTimeSpeed ();

    static void setRenderFrameRate (unsigned int);
    static void setUpdateTickRate (unsigned int);

    static void setTimeSpeed (double);

    static void run ();
    static void freeze ();
    static bool isRunning ();

private:

    static void update (SpeedGovernor&, unsigned int&, double&, double&, bool&, bool&, bool&);

    static void render (double);

    static void updateRenderTimings ();
    static void updateUpdateTimings ();

    static unsigned int m_renderFrameRate;
    static unsigned int m_updateTickRate;

    static double m_timeSpeed;

    static double m_renderSeconds;
    static double m_updateSeconds;
    static double m_perceivedUpdateSeconds;

    static SpeedGovernor m_renderLoopGovernor;
    static SpeedGovernor m_updateLoopGovernor;

    static bool m_windowOpen;
    static bool m_isRunning;

    static bool m_renderLoopRunning;
    static bool m_updateLoopRunning;

    static std::thread m_updateThread;

};
}

#endif
