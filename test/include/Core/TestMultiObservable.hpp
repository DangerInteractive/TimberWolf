#ifndef TWT_CLASS_TESTMULTIOBSERVABLE
#define TWT_CLASS_TESTMULTIOBSERVABLE

#include "../../../include/TimberWolf/Core/ObserverAction.hpp"
#include "../../../include/TimberWolf/Core/MultiObservable.hpp"

#include "TestObserver.hpp"

namespace twt {
class TestMultiObservable : public tw::MultiObservable<TestObserver> {

public:

    TestMultiObservable () = default;
    ~TestMultiObservable () = default;

    TestMultiObservable (TestMultiObservable&&) = default;
    TestMultiObservable& operator = (TestMultiObservable&&) = default;

    TestMultiObservable (const TestMultiObservable&) = default;
    TestMultiObservable& operator = (const TestMultiObservable&) = default;

    void testNotify (const tw::ObserverAction<TestObserver>&);

};
}

#endif
