#include "../../include/Core/TestObserver.hpp"

bool twt::TestObserver::wasNotified () const noexcept {

    return m_notified;

}

int twt::TestObserver::getNotifiedValue () const noexcept {

    return m_value;

}

void twt::TestObserver::onTestNotification (int value) noexcept {

    m_notified = true;
    m_value = value;

}
