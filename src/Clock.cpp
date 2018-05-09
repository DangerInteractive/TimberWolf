#include "../include/Clock.hpp"

/**
 * @class tw::Clock
 *
 * Class for tracking elapsed time from its instantiation or reset time.
 */

/**
 * tw::Clock default constructor counting from the moment it is instantiated.
 */
tw::Clock::Clock ()
: m_resetTime(std::chrono::high_resolution_clock::now()) {}

/**
 * Get the time point when the last clock reset occurred.
 *
 * @return the last reset time
 */
std::chrono::time_point<std::chrono::high_resolution_clock> tw::Clock::getResetTime () const {

    return m_resetTime;

}

/**
 * Get the number of seconds since the last clock reset.
 *
 * @return seconds since last reset time
 */
double tw::Clock::getElapsedSeconds () const {

    std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - m_resetTime;

    return duration.count();

}

/**
 * Get the number of milliseconds since the last clock reset
 *
 * @return milliseconds since last reset time
 */
long long tw::Clock::getElapsedMilliseconds () const {

    std::chrono::duration<long long, std::milli> duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - m_resetTime
        );

    return duration.count();

}

/**
 * Get the number of microseconds since the last clock reset
 *
 * @return microseconds since last reset time
 */
long long tw::Clock::getElapsedMicroseconds () const {

    std::chrono::duration<long long, std::micro> duration =
        std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now() - m_resetTime
        );

    return duration.count();

}

/**
 * Get the number of nanoseconds since the last clock reset
 *
 * @return nanoseconds since last reset time
 */
long long tw::Clock::getElapsedNanoseconds () const {

    std::chrono::duration<long long, std::nano> duration =
        std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now() - m_resetTime
        );

    return duration.count();

}

/**
 * Reset the clock, causing the clock to count up from the moment it's called.
 */
void tw::Clock::reset () {

    m_resetTime = std::chrono::high_resolution_clock::now();

}
