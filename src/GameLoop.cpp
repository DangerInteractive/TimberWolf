#include "../include/GameLoop.hpp"

/**
 * @class tw::GameLoop
 *
 * Static class representing the inner game loop and its threads, and providing
 * controls for the rendering and update rates and speeds.
 */

unsigned int tw::GameLoop::getRenderFrameRate () {

    return m_renderFrameRate;

}

unsigned int tw::GameLoop::getUpdateTickRate () {

    return m_updateTickRate;

}

double tw::GameLoop::getTimeSpeed () {

    return m_timeSpeed;

}

void tw::GameLoop::setRenderFrameRate (unsigned int framesPerSecond) {

    m_renderFrameRate = framesPerSecond;
    updateRenderTimings();

}

void tw::GameLoop::setUpdateTickRate (unsigned int ticksPerSecond) {

    m_updateTickRate = ticksPerSecond;
    updateUpdateTimings();

}

void tw::GameLoop::setTimeSpeed (double timeSpeed) {

    m_timeSpeed = timeSpeed;
    updateUpdateTimings();

}

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
                    glClear(GL_COLOR_BUFFER_BIT);
                    glClear(GL_DEPTH_BUFFER_BIT);
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

void tw::GameLoop::freeze () {

    m_isRunning = false; // threads watching idle

}

bool tw::GameLoop::isRunning () {

    return m_isRunning;

}

void tw::GameLoop::render (double deltaTime) {

    GameStateManager::render(deltaTime);

}

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

void tw::GameLoop::updateRenderTimings () {

    m_renderSeconds = 1.0 / m_renderFrameRate;
    m_renderLoopGovernor.setSeconds(m_renderSeconds);

}

void tw::GameLoop::updateUpdateTimings () {

    m_updateSeconds = 1.0 / m_updateTickRate;
    m_perceivedUpdateSeconds = m_updateSeconds * m_timeSpeed;
    m_updateLoopGovernor.setSeconds(m_updateSeconds);

}

unsigned int tw::GameLoop::m_renderFrameRate = 60;
unsigned int tw::GameLoop::m_updateTickRate = 40;

double tw::GameLoop::m_timeSpeed = 1.0;

double tw::GameLoop::m_renderSeconds = 1.0 / 60.0;
double tw::GameLoop::m_updateSeconds = 1.0 / 40.0;
double tw::GameLoop::m_perceivedUpdateSeconds = 1.0 / 40.0;

tw::SpeedGovernor tw::GameLoop::m_renderLoopGovernor {false, false, 1.0 / 60.0};
tw::SpeedGovernor tw::GameLoop::m_updateLoopGovernor {true, true, 1.0 / 40.0};

bool tw::GameLoop::m_windowOpen = false;
bool tw::GameLoop::m_isRunning = false;

bool tw::GameLoop::m_renderLoopRunning = false;
bool tw::GameLoop::m_updateLoopRunning = false;

std::thread tw::GameLoop::m_updateThread;
