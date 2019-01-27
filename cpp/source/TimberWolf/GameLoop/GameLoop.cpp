#include "../../../include/TimberWolf/GameLoop/GameLoop.hpp"

/**
 * @class tw::GameLoop
 *
 * Static class representing the inner game loop and its threads, and providing
 * controls for the rendering and update rates and speeds.
 */

/**
 * Get the number of iterations of the render loop per second.
 *
 * @return render frame rate in Hz
 */
unsigned int tw::GameLoop::getRenderFrameRate () {

    return m_renderFrameRate;

}

/**
 * Get the number of iterations of the update loop per second.
 *
 * @return update tick rate in Hz
 */
unsigned int tw::GameLoop::getUpdateTickRate () {

    return m_updateTickRate;

}

/**
 * Get the ratio of the perceived passage of time in the game loop to the real
 * passage of time.
 *
 * @return game to real time ratio
 */
double tw::GameLoop::getTimeSpeed () {

    return m_timeSpeed;

}

/**
 * Set the number of iterations the render loop executes per second.
 *
 * @param framesPerSecond render frame rate in Hz
 */
void tw::GameLoop::setRenderFrameRate (unsigned int framesPerSecond) {

    m_renderFrameRate = framesPerSecond;
    updateRenderTimings();

}

/**
 * Set the number of iterations the update loop executes per second.
 *
 * @param ticksPerSecond update tick rate in Hz
 */
void tw::GameLoop::setUpdateTickRate (unsigned int ticksPerSecond) {

    m_updateTickRate = ticksPerSecond;
    updateUpdateTimings();

}

/**
 * Set the ratio of perceived passage of time in the game loop to the real
 * passage of time.
 *
 * @param timeSpeed game to real time ratio
 */
void tw::GameLoop::setTimeSpeed (double timeSpeed) {

    m_timeSpeed = timeSpeed;
    updateUpdateTimings();

}

/**
 * Run the game loop. This will start the update loop in another thread, then
 * run the render loop on this thread, blocking further execution until the game
 * loop is stopped, which will wait for both the render and update loops to stop
 * before proceeding.
 */
void tw::GameLoop::run () {

    m_windowOpen = true;
    m_isRunning = true; // threads call StateManager's render/update/input

    if (!m_updateLoopRunning) {
        m_updateThread = std::thread(
            update,
            std::ref(m_updateLoopGovernor),
            std::ref(m_updateTickRate),
            std::ref(m_updateSeconds),
            std::ref(m_perceivedUpdateSeconds),
            std::ref(m_windowOpen),
            std::ref(m_isRunning),
            std::ref(m_updateLoopRunning)
        );
    }

    if (!m_renderLoopRunning) {

        m_renderLoopRunning = true;

        GLFWwindow* context = Window::getContext();
        Window::makeContextCurrent();

        glfwSetKeyCallback(context, GameStateManager::keyCallback);
        glfwSetCursorPosCallback(context, GameStateManager::cursorCallback);
        glfwSetCursorEnterCallback(context, GameStateManager::cursorInOutCallback);
        glfwSetMouseButtonCallback(context, GameStateManager::mouseButtonCallback);
        glfwSetScrollCallback(context, GameStateManager::scrollCallback);
        glfwSetDropCallback(context, GameStateManager::dropCallback);

        m_renderLoopGovernor.clearLag();
        m_renderLoopGovernor.reset();
        while (!glfwWindowShouldClose(context)) {

            auto deltaTime = m_updateLoopGovernor.getElapsedSeconds();

            if (m_isRunning) {

                if (context != NULL) {
                    glfwSwapBuffers(context);
                }

                glfwPollEvents();
                render(deltaTime * m_timeSpeed);

            }

            m_renderLoopGovernor.next();

        }

        m_windowOpen = false;
        m_renderLoopRunning = false;

    }

    m_updateThread.join();

}

/**
 * Freeze the game loop. This will cause both the render and update loops to
 * stop executing game state code until unfrozen, but neither loop will
 * terminate.
 */
void tw::GameLoop::freeze () {

    m_isRunning = false; // threads watching idle

}

/**
 * Check if the game loop is currently running.
 *
 * @return true if game loop is running, false if not
 */
bool tw::GameLoop::isRunning () {

    return m_isRunning;

}

/**
 * Perform the action of an iteration of the render loop. This calls out to game
 * state code in the active game states.
 *
 * @param deltaTime time since last iteration of the update loop in seconds
 */
void tw::GameLoop::render (double deltaTime) {

    GameStateManager::render(deltaTime);

}

/**
 * Inner loop code for the update loop. This function is executed on the update
 * thread instead of the main thread. This function reads and manipulates the
 * variables that it is provided.
 *
 * @param updateLoopGovernor     reference to the update loop governor variable
 * @param updateTickRate         reference to the update tick rate variable
 * @param updateSeconds          reference to the update seconds variable
 * @param perceivedUpdateSeconds reference to the perceived update seconds variable
 * @param windowOpen             reference to the window open flag
 * @param isRunning              reference to the is running flag
 * @param updateLoopRunning      reference to the update loop running flag
 */
void tw::GameLoop::update (
    SpeedGovernor& updateLoopGovernor,
    unsigned int& updateTickRate,
    double& updateSeconds,
    double& perceivedUpdateSeconds,
    bool& windowOpen,
    bool& isRunning,
    bool& updateLoopRunning
) {

    updateLoopRunning = true;

    m_updateLoopGovernor.clearLag();
    m_updateLoopGovernor.reset();
    while (windowOpen) {

        if (isRunning) {
            GameStateManager::update(perceivedUpdateSeconds);
        }

        m_updateLoopGovernor.next();

    }

    updateLoopRunning = false;

}

/**
 * Update cached timings for the update loop. This should always be called by
 * any methods of this class when any update loop timing setting is changed.
 */
void tw::GameLoop::updateRenderTimings () {

    m_renderSeconds = 1.0 / m_renderFrameRate;
    m_renderLoopGovernor.setSeconds(m_renderSeconds);

}

/**
 * Update cached timings for the render loop. This should always be called by
 * any methods of this class when any render loop timing setting is changed.
 */
void tw::GameLoop::updateUpdateTimings () {

    m_updateSeconds = 1.0 / m_updateTickRate;
    m_perceivedUpdateSeconds = m_updateSeconds * m_timeSpeed;
    m_updateLoopGovernor.setSeconds(m_updateSeconds);

}

unsigned int tw::GameLoop::m_renderFrameRate = 60; ///< iterations per second of the render loop
unsigned int tw::GameLoop::m_updateTickRate = 40; ///< iterations per second of the update loop

double tw::GameLoop::m_timeSpeed = 1.0; ///< ratio of perceived time vs real time

double tw::GameLoop::m_renderSeconds = 1.0 / 60.0; ///< seconds per iteration of the render loop
double tw::GameLoop::m_updateSeconds = 1.0 / 40.0; ///< seconds per iteration of the update loop
double tw::GameLoop::m_perceivedUpdateSeconds = 1.0 / 40.0; ///< perceived seconds passed per iteration of the update loop

tw::SpeedGovernor tw::GameLoop::m_renderLoopGovernor {false, false, 1.0 / 60.0}; ///< speed governor for the render loop
tw::SpeedGovernor tw::GameLoop::m_updateLoopGovernor {true, true, 1.0 / 40.0}; ///< speed governor for the update loop

bool tw::GameLoop::m_windowOpen = false; ///< whether or not the window is open
bool tw::GameLoop::m_isRunning = false; ///< whether or not the game loop is running

bool tw::GameLoop::m_renderLoopRunning = false; ///< whether or not the render loop is running
bool tw::GameLoop::m_updateLoopRunning = false; ///< whether or not the update loop is running

std::thread tw::GameLoop::m_updateThread; ///< handle for the update thread
