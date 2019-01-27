#ifndef TW_CLASS_CLOCK
#define TW_CLASS_CLOCK

/**
 * @file
 *
 * Header file for the tw::Clock class.
 */

#include <chrono>

namespace tw {
class Clock {

public:

    Clock ();
    ~Clock () = default;

    Clock (Clock&&) = default;
    Clock& operator = (Clock&&) = default;

    Clock (const Clock&) = default;
    Clock& operator = (const Clock&) = default;

    std::chrono::time_point<std::chrono::high_resolution_clock> getResetTime () const;

    double getElapsedSeconds () const;
    long long getElapsedMilliseconds () const;
    long long getElapsedMicroseconds () const;
    long long getElapsedNanoseconds () const;

    void reset ();

private:

    std::chrono::time_point<std::chrono::high_resolution_clock> m_resetTime;

};
}

#endif
