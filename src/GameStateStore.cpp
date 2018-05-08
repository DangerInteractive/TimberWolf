#include "../include/GameStateStore.hpp"

bool tw::GameStateStore::stateExists (const std::string& key) {

    if (m_stateMap.find(key) == m_stateMap.end()) {
        return false;
    } else {
        return true;
    }

}

std::shared_ptr<tw::GameState> tw::GameStateStore::getState (const std::string& key) {

    if (!stateExists(key)) {
        return nullptr;
    }

    return m_stateMap[key];

}

bool tw::GameStateStore::registerState (const std::string& key, const std::shared_ptr<GameState>& gameState) {

    if (stateExists(key)) {
        logStateAlreadyExists(key);
        return false;
    }

    m_stateMap.emplace(key, gameState);
    return true;

}

bool tw::GameStateStore::registerState (const std::string& key, GameState* gameState) {

    return registerState(key, std::shared_ptr<GameState>(gameState));

}

void tw::GameStateStore::deleteState (const std::string& key) {

    if (!stateExists(key)) {
        return;
    }

    m_stateMap[key].reset();
    m_stateMap.erase(key);

}

void tw::GameStateStore::logStateAlreadyExists (const std::string& key) {

    Log::warning("gamestatestore", "Game state with \"", key, "\" key already exists.");

}

std::map<std::string, std::shared_ptr<tw::GameState>> tw::GameStateStore::m_stateMap;
