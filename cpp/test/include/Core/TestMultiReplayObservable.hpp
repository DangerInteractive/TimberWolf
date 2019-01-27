#ifndef TWT_CLASS_TESTMULTIREPLAYOBSERVABLE
#define TWT_CLASS_TESTMULTIREPLAYOBSERVABLE

#include "../../../include/TimberWolf/Core/ObserverAction.hpp"
#include "../../../include/TimberWolf/Core/MultiReplayObservable.hpp"

#include "TestObserver.hpp"

namespace twt {
class TestMultiReplayObservable : public tw::MultiReplayObservable<TestObserver> {

public:

    TestMultiReplayObservable () = default;
    ~TestMultiReplayObservable () = default;

    TestMultiReplayObservable (TestMultiReplayObservable&&) = default;
    TestMultiReplayObservable& operator = (TestMultiReplayObservable&&) = default;

    TestMultiReplayObservable (const TestMultiReplayObservable&) = default;
    TestMultiReplayObservable& operator = (const TestMultiReplayObservable&) = default;

    void testNotify (const tw::ObserverAction<TestObserver>&);
    void testNotifyAndReplay (const tw::ObserverAction<TestObserver>&);

    void notifyValue (int);
    void notifyAndReplayValue (int);

};
}

#endif
