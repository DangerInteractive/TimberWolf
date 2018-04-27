#include "../include/ThreadManager.hpp"

void tw::ThreadManager::registerThread (const std::string& key, std::thread&& thread) {

    m_threads.emplace(key, std::move(thread));

}

std::unordered_map<std::string, std::thread> tw::ThreadManager::m_threads {};
