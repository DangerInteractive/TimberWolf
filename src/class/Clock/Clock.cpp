#include "Clock.hpp"

Clock::Clock ()
: m_resetTime(std::chrono::high_resolution_clock::now())
{}

std::chrono::time_point<std::chrono::high_resolution_clock> Clock::getResetTime () const {

    return m_resetTime;

}

double Clock::getElapsedSeconds () const {

    std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - m_resetTime;

    return duration.count();

}

long long Clock::getElapsedMilliseconds () const {

    std::chrono::duration<long long, std::milli> duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - m_resetTime
        );

    return duration.count();

}

long long Clock::getElapsedMicroseconds () const {

    std::chrono::duration<long long, std::micro> duration =
        std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now() - m_resetTime
        );

    return duration.count();

}

long long Clock::getElapsedNanoseconds () const {

    std::chrono::duration<long long, std::nano> duration =
        std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now() - m_resetTime
        );

    return duration.count();

}
