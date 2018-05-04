#include "../include/SpeedGovernor.hpp"

tw::SpeedGovernor::SpeedGovernor (bool fixedStep, bool catchUp, double seconds)
: m_fixedStep(fixedStep), m_catchUp(catchUp), m_seconds(seconds), m_frequency(1.0 / seconds) {}

bool tw::SpeedGovernor::fixedStepEnabled () const {

    return m_fixedStep;

}

bool tw::SpeedGovernor::catchUpEnabled () const {

    return m_catchUp;

}

double tw::SpeedGovernor::getSeconds () const {

    return m_seconds;

}

double tw::SpeedGovernor::getFrequency () const {

    return m_frequency;

}

long long tw::SpeedGovernor::getMilliseconds () const {

    return static_cast<long long>(getSeconds() * 1000.0);

}

long long tw::SpeedGovernor::getMicroseconds () const {

    return static_cast<long long>(getSeconds() * 1000000.0);

}

long long tw::SpeedGovernor::getNanoseconds () const {

    return static_cast<long long>(getSeconds() * 1000000000.0);

}

double tw::SpeedGovernor::getElapsedIntervals () const {

    return getElapsedSeconds() * getFrequency();

}

double tw::SpeedGovernor::getElapsedSeconds () const {

    return m_clock.getElapsedSeconds();

}

long long tw::SpeedGovernor::getElapsedMilliseconds () const {

    return m_clock.getElapsedMilliseconds();

}

long long tw::SpeedGovernor::getElapsedMicroseconds () const {

    return m_clock.getElapsedMicroseconds();

}

long long tw::SpeedGovernor::getElapsedNanoseconds () const {

    return m_clock.getElapsedNanoseconds();

}

double tw::SpeedGovernor::getEarlyIntervals () const {

    return getEarlySeconds() * getFrequency();

}

double tw::SpeedGovernor::getEarlySeconds () const {

    return getSeconds() - getElapsedSeconds();

}

long long tw::SpeedGovernor::getEarlyMilliseconds () const {

    return getMilliseconds() - getElapsedMilliseconds();

}

long long tw::SpeedGovernor::getEarlyMicroseconds () const {

    return getMicroseconds() - getElapsedMicroseconds();

}

long long tw::SpeedGovernor::getEarlyNanoseconds () const {

    return getNanoseconds() - getElapsedNanoseconds();

}

double tw::SpeedGovernor::getLateIntervals () const {

    return -getEarlyIntervals();

}

double tw::SpeedGovernor::getLateSeconds () const {

    return -getEarlySeconds();

}

long long tw::SpeedGovernor::getLateMilliseconds () const {

    return -getEarlyMilliseconds();

}

long long tw::SpeedGovernor::getLateMicroseconds () const {

    return -getEarlyMicroseconds();

}

long long tw::SpeedGovernor::getLateNanoseconds () const {

    return - getEarlyNanoseconds();

}

double tw::SpeedGovernor::getLagIntervals () const {

    return getLagSeconds() * getFrequency();

}

double tw::SpeedGovernor::getLagSeconds () const {

    return m_lag;

}

long long tw::SpeedGovernor::getLagMilliseconds () const {

    return getLagSeconds() * 1000;

}

long long tw::SpeedGovernor::getLagMicroseconds () const {

    return getLagSeconds() * 1000000;

}

long long tw::SpeedGovernor::getLagNanoseconds () const {

    return getLagSeconds() * 1000000000;

}

void tw::SpeedGovernor::enableFixedStep () {

    m_fixedStep = true;

}

void tw::SpeedGovernor::disableFixedStep () {

    m_fixedStep = false;

}

void tw::SpeedGovernor::enableCatchUp () {

    m_catchUp = true;

}

void tw::SpeedGovernor::disableCatchUp () {

    m_catchUp = false;

}

void tw::SpeedGovernor::clearLag () {

    m_lag = 0.0;

}

void tw::SpeedGovernor::setSeconds (double seconds) {

    m_seconds = seconds;
    m_frequency = 1.0 / seconds;

}

void tw::SpeedGovernor::setFrequency (double frequency) {

    m_seconds = 1.0 / frequency;
    m_frequency = frequency;

}

void tw::SpeedGovernor::setMilliseconds (long long milliseconds) {

    setSeconds(static_cast<double>(milliseconds) / 1000.0);

}

void tw::SpeedGovernor::setMicroseconds (long long microseconds) {

    setSeconds(static_cast<double>(microseconds) / 1000000.0);

}

void tw::SpeedGovernor::setNanoseconds (long long nanoseconds) {

    setSeconds(static_cast<double>(nanoseconds) / 1000000000.0);

}

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

void tw::SpeedGovernor::reset () {

    m_clock.reset();

}
