#include "../include/GameLoop.hpp"

void tw::GameLoop::setRenderFrameRate (unsigned int framesPerSecond) {

    m_renderFrameRate = framesPerSecond;
    m_renderSeconds = 1.0 / framesPerSecond;

}

void tw::GameLoop::setUpdateTickRate (unsigned int ticksPerSecond) {

    m_updateTickRate = ticksPerSecond;
    m_updateSeconds = 1.0 / ticksPerSecond;

}

void tw::GameLoop::run () {

    m_windowOpen = true;
    m_isRunning = true; // threads call StateManager's render/update/input

    if (!m_updateLoopRunning) {
        m_updateThread = std::thread(
            update,
            std::ref(m_updateLoopClock),
            std::ref(m_updateTickRate),
            std::ref(m_updateSeconds),
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

        while (!glfwWindowShouldClose(context)) {

            m_renderLoopClock.reset();

            auto deltaTime = m_updateLoopClock.getElapsedSeconds();

            if (m_isRunning) {

                if (context != NULL) {
                    glClear(GL_COLOR_BUFFER_BIT);
                    glfwSwapBuffers(context);
                }

                glfwPollEvents();
                render(deltaTime);

            }

            auto elapsedTime = m_renderLoopClock.getElapsedSeconds();

            if (elapsedTime < m_renderSeconds) {
                std::this_thread::sleep_for(std::chrono::duration<double>(m_renderSeconds - elapsedTime));
            }

            m_renderLoopClock.reset();

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
    Clock& updateLoopClock,
    unsigned int& updateTickRate,
    double& updateSeconds,
    bool& windowOpen,
    bool& isRunning,
    bool& updateLoopRunning
) {

    updateLoopRunning = true;

    double deltaTime = updateSeconds;
    while (windowOpen) {

        auto startTime = updateLoopClock.getElapsedSeconds();

        if (isRunning) {

            int ticks = static_cast<int>(deltaTime * updateTickRate);
            for (int i = 0; i < ticks; ++i) {
                GameStateManager::update();
            }

        }

        auto elapsedTime = updateLoopClock.getElapsedSeconds();
        if (elapsedTime < updateSeconds) {
            std::this_thread::sleep_for(std::chrono::duration<double>(updateSeconds - elapsedTime));
        }

        deltaTime = updateLoopClock.getElapsedSeconds() - startTime;
        updateLoopClock.reset();

    }

    updateLoopRunning = false;

}

unsigned int tw::GameLoop::m_renderFrameRate = 60;
unsigned int tw::GameLoop::m_updateTickRate = 40;

double tw::GameLoop::m_renderSeconds = 1.0 / 60.0;
double tw::GameLoop::m_updateSeconds = 1.0 / 40.0;

tw::Clock tw::GameLoop::m_renderLoopClock;
tw::Clock tw::GameLoop::m_updateLoopClock;

bool tw::GameLoop::m_windowOpen = false;
bool tw::GameLoop::m_isRunning = false;

bool tw::GameLoop::m_renderLoopRunning = false;
bool tw::GameLoop::m_updateLoopRunning = false;

std::thread tw::GameLoop::m_updateThread;
