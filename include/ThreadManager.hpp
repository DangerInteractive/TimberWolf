#ifndef H_TW_THREADMANAGER
#define H_TW_THREADMANAGER

#include <unordered_map>
#include <string>
#include <thread>

namespace tw {
class ThreadManager {

public:

    ThreadManager () = delete; // static only
    ~ThreadManager () = delete;

    ThreadManager (ThreadManager&&) = delete;
    ThreadManager& operator = (ThreadManager&&) = delete;

    ThreadManager (const ThreadManager&) = delete;
    ThreadManager& operator = (const ThreadManager&) = delete;

    template <typename ...TArgs>
    static std::thread* makeThread (const std::string& key, TArgs&&... args) {

        registerThread(key, std::thread(std::forward<TArgs>(args)...));

        return &m_threads[key];

    }

    static void registerThread (const std::string&, std::thread&&);

private:

    static std::unordered_map<std::string, std::thread> m_threads;

};
}

#endif
