#include "Clock.hpp"

Clock::Clock ()
: m_resetTime(std::chrono::high_resolution_clock::now())
{}

std::chrono::time_point<std::chrono::high_resolution_clock> Clock::getResetTime () const {

    return m_resetTime;

}

double Clock::getElapsedSeconds () const {

    std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - m_resetTime;
    duration = std::chrono::duration_cast<std::chrono::seconds>(duration);

    return duration.count();

}

long long Clock::getElapsedMilliseconds () const {

    std::chrono::duration<long long> duration = std::chrono::high_resolution_clock::now() - m_resetTime;
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(duration);

    return duration.count();

}

long long Clock::getElapsedMicroseconds () const {

    std::chrono::duration<long long> duration = std::chrono::high_resolution_clock::now() - m_resetTime;
    duration = std::chrono::duration_cast<std::chrono::microseconds>(duration);

    return duration.count();

}

long long Clock::getElapsedNanoseconds () const {

    std::chrono::duration<long long> duration = std::chrono::high_resolution_clock::now() - m_resetTime;
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);

    return duration.count();

}
