#ifndef TWT_CLASS_TESTSINGLEREPLAYOBSERVABLE
#define TWT_CLASS_TESTSINGLEREPLAYOBSERVABLE

#include "../../../include/TimberWolf/Core/ObserverAction.hpp"
#include "../../../include/TimberWolf/Core/SingleReplayObservable.hpp"

#include "TestObserver.hpp"

namespace twt {
class TestSingleReplayObservable : public tw::SingleReplayObservable<TestObserver> {

public:

    TestSingleReplayObservable () = default;
    ~TestSingleReplayObservable () = default;

    TestSingleReplayObservable (TestSingleReplayObservable&&) = default;
    TestSingleReplayObservable& operator = (TestSingleReplayObservable&&) = default;

    TestSingleReplayObservable (const TestSingleReplayObservable&) = default;
    TestSingleReplayObservable& operator = (const TestSingleReplayObservable&) = default;

    void notifyValue (int);
    void notifyAndReplayValue (int);

};
}

#endif
