#include "GameLoop.hpp"

void GameLoop::setRenderFrameRate (int framesPerSecond) {

    m_renderFrameRate = framesPerSecond;
    m_renderSeconds = 1.0 / framesPerSecond;

}

void GameLoop::setUpdateTickRate (int ticksPerSecond) {

    m_updateTickRate = ticksPerSecond;
    m_updateSeconds = 1.0 / ticksPerSecond;

}

void GameLoop::run () {

    m_windowOpen = true;
    m_isRunning = true; // threads call StateManager's render/update/input

    if (!m_updateLoopRunning) {
        m_updateThread = std::thread(
            update,
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

            double deltaTime = m_renderSeconds;

            auto startTime = std::chrono::high_resolution_clock::now();

            if (m_isRunning) {

                if (context != NULL) {
                    glClear(GL_COLOR_BUFFER_BIT);
                    glfwSwapBuffers(context);
                }

                glfwPollEvents();
                render(deltaTime);

            }

            auto endTime = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> elapsedTime = endTime - startTime;

            if (elapsedTime.count() < m_renderSeconds) {
                std::this_thread::sleep_for(std::chrono::duration<double>(m_renderSeconds - elapsedTime.count()));
            }

            auto finalTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> finalElapsedTime = finalTime - startTime;
            deltaTime = finalElapsedTime.count();

        }

        m_windowOpen = false;
        m_renderLoopRunning = false;

    }

    m_updateThread.join();

}

void GameLoop::freeze () {

    m_isRunning = false; // threads watching idle

}

bool GameLoop::isRunning () {

    return m_isRunning;

}

void GameLoop::render (double deltaTime) {

    GameStateManager::render(deltaTime);

}

void GameLoop::update (
    int& updateTickRate,
    double& updateSeconds,
    bool& windowOpen,
    bool& isRunning,
    bool& updateLoopRunning
) {

    updateLoopRunning = true;

    while (windowOpen) {

        double deltaTime = updateSeconds;

        auto startTime = std::chrono::high_resolution_clock::now();

        if (isRunning) {

            int ticks = static_cast<int>(deltaTime * updateTickRate);
            for (int i = 0; i < ticks; ++i) {
                GameStateManager::update();
            }

        }

        auto endTime = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> elapsedTime = endTime - startTime;

        if (elapsedTime.count() < updateSeconds) {
            std::this_thread::sleep_for(std::chrono::duration<double>(updateSeconds - elapsedTime.count()));
        }

        auto finalTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> finalElapsedTime = finalTime - startTime;
        deltaTime = finalElapsedTime.count();

    }

    updateLoopRunning = false;

}

int GameLoop::m_renderFrameRate = 60;
int GameLoop::m_updateTickRate = 40;

double GameLoop::m_renderSeconds = 1.0 / 60.0;
double GameLoop::m_updateSeconds = 1.0 / 40.0;

bool GameLoop::m_windowOpen = false;
bool GameLoop::m_isRunning = false;

bool GameLoop::m_renderLoopRunning = false;
bool GameLoop::m_updateLoopRunning = false;

std::thread GameLoop::m_updateThread;
