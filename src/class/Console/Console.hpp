#ifndef H_CLASS_CONSOLE
#define H_CLASS_CONSOLE

#include <iostream>
#include <mutex>

namespace tw {
class Console {

public:

    Console () = delete; // static only
    ~Console () = delete;

    Console (Console&&) = delete;
    Console& operator = (Console&&) = delete;

    Console (const Console&) = delete;
    Console& operator = (const Console&) = delete;

    template <typename ...T>
    static void stdout (T&&... message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        (std::cout << ... << std::forward<T>(message));

    }

    template <typename ...T>
    static void stdoutLine (T&&... message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        (std::cout << ... << std::forward<T>(message)) << std::endl;

    }

    template <typename ...T>
    static void stderr (T&&... message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        (std::cerr << ... << std::forward<T>(message));

    }

    template <typename ...T>
    static void stderrLine (T&&... message) {

        std::unique_lock<std::mutex> lock(m_mutex);

        (std::cerr << ... << std::forward<T>(message)) << std::endl;

    }

private:

    static std::mutex m_mutex;

};
}

#endif
