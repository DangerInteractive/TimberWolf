#include "Clock.hpp"

tw::Clock::Clock ()
: m_resetTime(std::chrono::high_resolution_clock::now()) {}

std::chrono::time_point<std::chrono::high_resolution_clock> tw::Clock::getResetTime () const {

    return m_resetTime;

}

double tw::Clock::getElapsedSeconds () const {

    std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - m_resetTime;

    return duration.count();

}

long long tw::Clock::getElapsedMilliseconds () const {

    std::chrono::duration<long long, std::milli> duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - m_resetTime
        );

    return duration.count();

}

long long tw::Clock::getElapsedMicroseconds () const {

    std::chrono::duration<long long, std::micro> duration =
        std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now() - m_resetTime
        );

    return duration.count();

}

long long tw::Clock::getElapsedNanoseconds () const {

    std::chrono::duration<long long, std::nano> duration =
        std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now() - m_resetTime
        );

    return duration.count();

}

void tw::Clock::reset () {

    m_resetTime = std::chrono::high_resolution_clock::now();

}
