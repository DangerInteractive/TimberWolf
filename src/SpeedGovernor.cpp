#include "../include/SpeedGovernor.hpp"

/**
 * @class tw::SpeedGovernor
 *
 * Time tracking object that controls the execution speed of a looping thread by
 * setting a minimum time per loop, and sleeping for the remaining time when
 * running fast. When running slow, it has different handling modes. The fixed
 * step setting causes the loop to guarantee each execution represents the same
 * time difference. The catch-up setting causes the loop to keep track of how
 * much time it lags behind where it should be, and it will try to run extra
 * iterations to catch up that missing time.
 */

/**
 * Constructor taking in boolean flags for fixed-step and catch-up settings, as
 * well as the minimum number of seconds between loop iterations.
 *
 * @param fixedStep true to enable fixed-step mode, false to disable
 * @param catchUp   true to enable catch-up mode, false to disable
 * @param seconds   minimum number of seconds between each iteration
 */
tw::SpeedGovernor::SpeedGovernor (bool fixedStep, bool catchUp, double seconds)
: m_fixedStep(fixedStep), m_catchUp(catchUp), m_seconds(seconds), m_frequency(1.0 / seconds) {}

/**
 * Check if fixed-step mode is enabled. If it is enabled, this means that the
 * loop will always advance by a fixed number of seconds instead of allowing
 * variations. This is to prevent floating point rounding errors in simulations
 * where each iteration affects the next.
 *
 * @return true if fixed-step mode is enabled, false if not
 */
bool tw::SpeedGovernor::fixedStepEnabled () const {

    return m_fixedStep;

}

/**
 * Check if catch-up mode is enabled. If it is enabled, this means that the loop
 * will attempt to catch up with the expected time after lagging behind. This is
 * to prevent synchronization issues in applications that are meant to be
 * real-time or where independent clients are connected.
 *
 * @return true if catch-up mode is enabled, false if not
 */
bool tw::SpeedGovernor::catchUpEnabled () const {

    return m_catchUp;

}

/**
 * Get the minimum number of seconds for each loop iteration. This is equivalent
 * to the inverse of the frequency.
 *
 * @return minimum number of seconds for each loop iteration
 */
double tw::SpeedGovernor::getSeconds () const {

    return m_seconds;

}

/**
 * Get the maximum number of iterations per second. This is equivalent to the
 * inverse of the minimum seconds.
 *
 * @return maximum number of iterations per second
 */
double tw::SpeedGovernor::getFrequency () const {

    return m_frequency;

}

/**
 * Get the minimum number of milliseconds for each loop iteration. This value is
 * cast to an integral type, and so the value is truncated to the next lower
 * millisecond.
 *
 * @return truncated minimum number of milliseconds per iteration
 */
long long tw::SpeedGovernor::getMilliseconds () const {

    return static_cast<long long>(getSeconds() * 1000.0);

}

/**
 * Get the minimum number of microseconds for each loop iteration. This value is
 * cast to an integral type, and so the value is truncated to the next lower
 * microsecond.
 *
 * @return truncated minimum number of microseconds per iteration
 */
long long tw::SpeedGovernor::getMicroseconds () const {

    return static_cast<long long>(getSeconds() * 1000000.0);

}

/**
 * Get the minimum number of nanoseconds for each loop iteration. This value is
 * cast to an integral type, and so the value is truncated to the next lower
 * nanosecond.
 *
 * @return truncated minimum number of nanoseconds per iteration
 */
long long tw::SpeedGovernor::getNanoseconds () const {

    return static_cast<long long>(getSeconds() * 1000000000.0);

}

/**
 * Get the number of intervals (minimum seconds) that have passed since the last
 * reset.
 *
 * @return number of intervals elapsed since the last reset
 */
double tw::SpeedGovernor::getElapsedIntervals () const {

    return getElapsedSeconds() * getFrequency();

}

/**
 * Get the number of seconds that have passed since the last reset.
 *
 * @return number of seconds elapsed since the last reset
 */
double tw::SpeedGovernor::getElapsedSeconds () const {

    return m_clock.getElapsedSeconds();

}

/**
 * Get the number of milliseconds that have passed since the last reset. This
 * value is cast to an integral type, and so the value is truncated to the next
 * lower millisecond.
 *
 * @return truncated number of milliseconds elapsed since the last reset
 */
long long tw::SpeedGovernor::getElapsedMilliseconds () const {

    return m_clock.getElapsedMilliseconds();

}

/**
 * Get the number of microseconds that have passed since the last reset. This
 * value is cast to an integral type, and so the value is truncated to the next
 * lower microsecond.
 *
 * @return truncated number of microseconds elapsed since the last reset
 */
long long tw::SpeedGovernor::getElapsedMicroseconds () const {

    return m_clock.getElapsedMicroseconds();

}

/**
 * Get the number of nanoseconds that have passed since the last reset. This
 * value is cast to an integral type, and so the value is truncated to the next
 * lower nanosecond.
 *
 * @return truncated number of nanoseconds elapsed since the last reset
 */
long long tw::SpeedGovernor::getElapsedNanoseconds () const {

    return m_clock.getElapsedNanoseconds();

}

/**
 * Get the number of intervals (minimum seconds) until the minimum time has been
 * elapsed. Note that this will never be greater than 1.
 *
 * @return number of intervals until the minimum time has elapsed
 */
double tw::SpeedGovernor::getEarlyIntervals () const {

    return getEarlySeconds() * getFrequency();

}

/**
 * Get the number of seconds until the minimum time has been elapsed.
 *
 * @return number of seconds until the minimum time has been elapsed.
 */
double tw::SpeedGovernor::getEarlySeconds () const {

    return getSeconds() - getElapsedSeconds();

}

/**
 * Get the number of milliseconds until the minimum time has been elapsed. This
 * value is cast to an integral type, and so the value is truncated to the next
 * lower millisecond.
 *
 * @return truncated number of milliseconds until the minimum time is elapsed
 */
long long tw::SpeedGovernor::getEarlyMilliseconds () const {

    return getMilliseconds() - getElapsedMilliseconds();

}

/**
 * Get the number of microseconds until the minimum time has been elapsed. This
 * value is cast to an integral type, and so the value is truncated to the next
 * lower microsecond.
 *
 * @return truncated number of microseconds until the minimum time is elapsed
 */
long long tw::SpeedGovernor::getEarlyMicroseconds () const {

    return getMicroseconds() - getElapsedMicroseconds();

}

/**
 * Get the number of nanoseconds until the minimum time has been elapsed. This
 * value is cast to an integral type, and so the value is truncated to the next
 * lower nanosecond.
 *
 * @return truncated number of nanoseconds until the minimum time is elapsed
 */
long long tw::SpeedGovernor::getEarlyNanoseconds () const {

    return getNanoseconds() - getElapsedNanoseconds();

}

/**
 * Get the number of intervals (minimum seconds) elapsed since the minimum time
 * has elapsed. Note that this will never be less than -1.
 *
 * @return number of intervals since the minimum time elapsed
 */
double tw::SpeedGovernor::getLateIntervals () const {

    return -getEarlyIntervals();

}

/**
 * Get the number of seconds elapsed since the minimum time has elapsed.
 *
 * @return number of seconds since the minimum time elapsed
 */
double tw::SpeedGovernor::getLateSeconds () const {

    return -getEarlySeconds();

}

/**
 * Get the number of milliseconds elapsed since the minimum time has elapsed.
 * This value is cast to an integral type, and so the value is truncated to the
 * next lower millisecond.
 *
 * @return truncated number of milliseconds until the minimum time is elapsed
 */
long long tw::SpeedGovernor::getLateMilliseconds () const {

    return -getEarlyMilliseconds();

}

/**
 * Get the number of microseconds elapsed since the minimum time has elapsed.
 * This value is cast to an integral type, and so the value is truncated to the
 * next lower microsecond.
 *
 * @return truncated number of microseconds until the minimum time is elapsed
 */
long long tw::SpeedGovernor::getLateMicroseconds () const {

    return -getEarlyMicroseconds();

}

/**
 * Get the number of nanoseconds elapsed since the minimum time has elapsed.
 * This value is cast to an integral type, and so the value is truncated to the
 * next lower nanosecond.
 *
 * @return truncated number of nanoseconds until the minimum time is elapsed
 */
long long tw::SpeedGovernor::getLateNanoseconds () const {

    return - getEarlyNanoseconds();

}

/**
 * Get the number of intervals (minimum seconds) behind the expected time the
 * loop is. This value is only tracked if catch-up is enabled, inc which case it
 * accumulates when iterations finish late.
 *
 * @return number of intervals behind the expected time
 */
double tw::SpeedGovernor::getLagIntervals () const {

    return getLagSeconds() * getFrequency();

}

/**
 * Get the number of seconds behind the expected time the loop is. This value
 * is only tracked if catch-up is enabled, in which case it accumulates when
 * iterations finish late.
 *
 * @return number of seconds behind the expected time
 */
double tw::SpeedGovernor::getLagSeconds () const {

    return m_lag;

}

/**
 * Get the number of milliseconds behind the expected time the loop is. This
 * value is only tracked if catch-up is enabled, in which case it accumulates
 * when iterations finish late. This value is cast to an integral type, and so
 * the value is truncated to the next lower millisecond.
 *
 * @return truncated number of milliseconds behind the expected time
 */
long long tw::SpeedGovernor::getLagMilliseconds () const {

    return getLagSeconds() * 1000;

}

/**
 * Get the number of microseconds behind the expected time the loop is. This
 * value is only tracked if catch-up is enabled, in which case it accumulates
 * when iterations finish late. This value is cast to an integral type, and so
 * the value is truncated to the next lower microsecond.
 *
 * @return truncated number of microseconds behind the expected time
 */
long long tw::SpeedGovernor::getLagMicroseconds () const {

    return getLagSeconds() * 1000000;

}

/**
 * Get the number of nanoseconds behind the expected time the loop is. This
 * value is only tracked if catch-up is enabled, in which case it accumulates
 * when iterations finish late. This value is cast to an integral type, and so
 * the value is truncated to the next lower nanosecond.
 *
 * @return truncated number of nanoseconds behind the expected time
 */
long long tw::SpeedGovernor::getLagNanoseconds () const {

    return getLagSeconds() * 1000000000;

}

/**
 * Enable fixed-step mode. This will cause the loop to advance time by fixed
 * intervals instead of allowing variation. This is meant to prevent floating
 * point rounding errors when each loop affects the next.
 */
void tw::SpeedGovernor::enableFixedStep () {

    m_fixedStep = true;

}

/**
 * Disable fixed-step mode. This will cause the loop to allow advancing time by
 * varying intervals on each loop. If each iteration has an effect on the next,
 * this can cause computers of differing speeds to come up with different states
 * given the same input.
 */
void tw::SpeedGovernor::disableFixedStep () {

    m_fixedStep = false;

}

/**
 * Enable catch-up mode. This will cause the loop to try to keep up with the
 * expected time by dropping the minimum time temporarily until it is caught up,
 * as opposed to ignoring lag.
 */
void tw::SpeedGovernor::enableCatchUp () {

    m_catchUp = true;

}

/**
 * Disable catch-up mode. This will cause the loop to ignore lag, as opposed to
 * attempting to keep up with the expected time by temporarily dropping the
 * minimum time.
 */
void tw::SpeedGovernor::disableCatchUp () {

    m_catchUp = false;

}

/**
 * Sideload the accumulated lag value to a specific number of seconds.
 *
 * @param lag number of seconds to which to set the accumulated lag
 */
void tw::SpeedGovernor::setLag (double lag) {

    m_lag = lag;

}

/**
 * Push the given number of seconds onto the accumulated lag.
 *
 * @param lag number of seconds to add to the accumulated lag
 */
void tw::SpeedGovernor::gainLag (double lag) {

    auto newLag = m_lag + lag;

    if (newLag < 0) {
        m_lag = 0;
    } else {
        m_lag = newLag;
    }

}

/**
 * Remove the given number of seconds from the accumulated lag.
 *
 * @param lag number of seconds to remove from the accumulated lag
 */
void tw::SpeedGovernor::loseLag (double lag) {

    gainLag(-lag);

}

/**
 * Remove all accumulated lag.
 */
void tw::SpeedGovernor::clearLag () {

    m_lag = 0.0;

}

/**
 * Set the minimum number of seconds allowed per iteration. Note that this is
 * equivalent to the inverse of the frequency.
 *
 * @param seconds minimum number of seconds per iteration
 */
void tw::SpeedGovernor::setSeconds (double seconds) {

    m_seconds = seconds;
    m_frequency = 1.0 / seconds;

}

/**
 * Set the maximum number of iterations per second. Note that this is equivalent
 * to the inverse of the minimum number of seconds.
 *
 * @param frequency maximum number of iterations per second
 */
void tw::SpeedGovernor::setFrequency (double frequency) {

    m_seconds = 1.0 / frequency;
    m_frequency = frequency;

}

/**
 * Set the minimum number of milliseconds allowed per iteration.
 *
 * @param milliseconds minimum number of milliseconds per iteration
 */
void tw::SpeedGovernor::setMilliseconds (long long milliseconds) {

    setSeconds(static_cast<double>(milliseconds) / 1000.0);

}

/**
 * Set the minimum number of microseconds allowed per iteration.
 *
 * @param microseconds minimum number of microseconds per iteration
 */
void tw::SpeedGovernor::setMicroseconds (long long microseconds) {

    setSeconds(static_cast<double>(microseconds) / 1000000.0);

}

/**
 * Set the minimum number of nanoseconds allowed per iteration.
 *
 * @param nanoseconds minimum number of nanoseconds per iteration
 */
void tw::SpeedGovernor::setNanoseconds (long long nanoseconds) {

    setSeconds(static_cast<double>(nanoseconds) / 1000000000.0);

}

/**
 * Notify the governor that the loop is advancing to the next iteration. This
 * will reset the timer and cause the thread to wait for the required time.
 *
 * @return number of seconds elapsed since the minimum time elapsed
 */
double tw::SpeedGovernor::next () {

    auto catchUp = catchUpEnabled();
    auto fixedStep = fixedStepEnabled();
    auto timeout = getSeconds();
    auto elapsed = getElapsedSeconds();
    auto lag = catchUp ? getLagSeconds() : 0.0;

    if (elapsed + lag < timeout) {
        std::this_thread::sleep_for(std::chrono::duration<double>(timeout - elapsed));
    }

    auto late = fixedStep ? 0.0 : getLateSeconds();
    reset();

    if (catchUp && fixedStep) {
        loseLag(getSeconds());
    }

    return late;

}

/**
 * Reset the clock, setting elapsed time back to zero.
 */
void tw::SpeedGovernor::reset () {

    m_clock.reset();

}
