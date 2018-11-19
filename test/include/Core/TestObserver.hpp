#ifndef TWT_CLASS_TESTOBSERVER
#define TWT_CLASS_TESTOBSERVER

#include "../../../include/TimberWolf/Core/Observer.hpp"
#include "../../../include/TimberWolf/Core/ObserverAction.hpp"

namespace twt {
class TestObserver : public tw::Observer {

public:

    TestObserver () = default;
    ~TestObserver () = default;

    TestObserver (TestObserver&&) = default;
    TestObserver& operator = (TestObserver&&) = default;

    TestObserver (const TestObserver&) = default;
    TestObserver& operator = (const TestObserver&) = default;

    bool wasNotified () const noexcept;
    int getNotifiedValue () const noexcept;

    virtual void onTestNotification (int) noexcept;

private:

    bool m_notified {false};
    int m_value {0};

};
}

#endif
