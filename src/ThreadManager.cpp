#include "../include/ThreadManager.hpp"

/**
 * @class tw::ThreadManager
 *
 * Under construction. Static object cache that eeps track of the game's
 * threads.
 */

void tw::ThreadManager::registerThread (const std::string& key, std::thread&& thread) {

    m_threads.emplace(key, std::move(thread));

}

std::unordered_map<std::string, std::thread> tw::ThreadManager::m_threads {};
