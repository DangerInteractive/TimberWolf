#include "../../../include/TimberWolf/Core/ThreadManager.hpp"

/**
 * @class tw::ThreadManager
 *
 * Under construction. Static object cache that keeps track of the game's
 * threads.
 */

/**
 * Move an rvalue to a std::thread into the thread map under a given std::string
 * key.
 *
 * @param key thread key
 * @param thread rvalue to thread
 */
void tw::ThreadManager::registerThread (const std::string& key, std::thread&& thread) {

    m_threads.emplace(key, std::move(thread));

}

std::unordered_map<std::string, std::thread> tw::ThreadManager::m_threads {}; ///< thread cache
