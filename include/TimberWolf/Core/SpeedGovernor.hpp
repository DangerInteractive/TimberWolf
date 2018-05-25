#ifndef H_TW_SPEEDGOVERNOR
#define H_TW_SPEEDGOVERNOR

/**
 * @file
 *
 * Header file for the tw::SpeedGovernor class.
 */

#include <thread>
#include <chrono>
#include "Clock.hpp"

namespace tw {
class SpeedGovernor {

public:

    SpeedGovernor () = default;
    SpeedGovernor (bool, bool, double);
    ~SpeedGovernor () = default;

    SpeedGovernor (SpeedGovernor&&) = default;
    SpeedGovernor& operator = (SpeedGovernor&&) = default;

    SpeedGovernor (const SpeedGovernor&) = default;
    SpeedGovernor& operator = (const SpeedGovernor&) = default;

    bool fixedStepEnabled () const;
    bool catchUpEnabled () const;

    double getSeconds () const;
    double getFrequency () const;
    long long getMilliseconds () const;
    long long getMicroseconds () const;
    long long getNanoseconds () const;

    double getElapsedIntervals () const;
    double getElapsedSeconds () const;
    long long getElapsedMilliseconds () const;
    long long getElapsedMicroseconds () const;
    long long getElapsedNanoseconds () const;

    double getEarlyIntervals () const;
    double getEarlySeconds () const;
    long long getEarlyMilliseconds () const;
    long long getEarlyMicroseconds () const;
    long long getEarlyNanoseconds () const;

    double getLateIntervals () const;
    double getLateSeconds () const;
    long long getLateMilliseconds () const;
    long long getLateMicroseconds () const;
    long long getLateNanoseconds () const;

    double getLagIntervals () const;
    double getLagSeconds () const;
    long long getLagMilliseconds () const;
    long long getLagMicroseconds () const;
    long long getLagNanoseconds () const;

    void enableFixedStep ();
    void disableFixedStep ();

    void enableCatchUp ();
    void disableCatchUp ();

    void setLag (double);
    void gainLag (double);
    void loseLag (double);
    void clearLag ();

    void setSeconds (double);
    void setFrequency (double);
    void setMilliseconds (long long);
    void setMicroseconds (long long);
    void setNanoseconds (long long);

    double next ();

    void reset ();

private:

    bool m_fixedStep {false};
    bool m_catchUp {false};
    double m_seconds {0.0};
    double m_frequency {1.0 / 0.0};

    Clock m_clock;
    double m_lag {0.0};

};
}

#endif
