#include "../../../include/TimberWolf/GameLoop/GameStateStore.hpp"

/**
 * @class tw::GameStateStore
 *
 * Static map-based object cache keeping track of polymorphic GameState objects
 * under std::string keys.
 */

/**
 * Check if a game state with the given std::string key already exists in the
 * cache.
 *
 * @param key game state key
 * @return true if the key already exists, false if not
 */
bool tw::GameStateStore::stateExists (const std::string& key) {

    if (m_stateMap.find(key) == m_stateMap.end()) {
        return false;
    } else {
        return true;
    }

}

/**
 * Get a game state from the cache with the given std::string key, or, if the
 * key is not found, you will get a null pointer.
 *
 * @param key shared pointer to the game state with the given key, if found, null pointer otherwise
 */
std::shared_ptr<tw::GameState> tw::GameStateStore::getState (const std::string& key) {

    if (!stateExists(key)) {
        return nullptr;
    }

    return m_stateMap[key];

}

/**
 * @fn tw::GameStateStore::makeState
 *
 * Factory method that creates a shared_ptr to a game state polymorphically
 * (define class with first template variable). All arguments after the first
 * will be perfectly forwarded to the constructor for the given class, which
 * will be placed into the cache and then returned.
 *
 * @tparam TState type of state to be created (must extend tw::GameState)
 * @tparam TArg   types of arguments passed to TState constructor (deduced automatically)
 * @param key     key to store the game state under
 * @param args    variadic arguments to pass to TState constructor
 * @return shared pointer to created game state on success, null pointer on failure
 */

/**
 * Register (store) a given std::shared_ptr to a game state in the cache under
 * the given std::string key.
 *
 * @param key       key to store the game state under
 * @param gameState shared pointer to the game state
 * @return true if the state was stored successfully, false if not
 */
bool tw::GameStateStore::registerState (const std::string& key, const std::shared_ptr<GameState>& gameState) {

    if (stateExists(key)) {
        logStateAlreadyExists(key);
        return false;
    }

    m_stateMap.emplace(key, gameState);
    return true;

}

/**
 * Register (store) a given pointer to a game state in the cache uder the given
 * std::string key. Note that even though you pass this as a regular pointer, it
 * will be converted into a shared pointer, and as such, removing it from the
 * cache will most likely delete it from memory.
 *
 * @param key       key to store the game state under
 * @param gameState pointer to the game state
 * @return true if the state was stored successfully, false if not
 */
bool tw::GameStateStore::registerState (const std::string& key, GameState* gameState) {

    return registerState(key, std::shared_ptr<GameState>(gameState));

}

/**
 * Remove the game state with the gien key from the cache. Note that since the
 * game state is kept as a shared pointer, deleting it will not necessarily free
 * its memory. Other references will have to fall out of scope first.
 *
 * @param key key of state to delete
 */
void tw::GameStateStore::deleteState (const std::string& key) {

    if (!stateExists(key)) {
        return;
    }

    m_stateMap[key].reset();
    m_stateMap.erase(key);

}

/**
 * Log a failure due to a game state key that already existed and would have
 * been implicitly overwritten otherwise.
 *
 * @param key key that was attempted to be implicitly overwritten
 */
void tw::GameStateStore::logStateAlreadyExists (const std::string& key) {

    Log::warning("gamestatestore", "Game state with \"", key, "\" key already exists.");

}

std::unordered_map<std::string, std::shared_ptr<tw::GameState>> tw::GameStateStore::m_stateMap; ///< Map of cached keys and game states.
