#ifndef TWT_CLASS_TESTSINGLEOBSERVABLE
#define TWT_CLASS_TESTSINGLEOBSERVABLE

#include <iostream>

#include "../../../include/TimberWolf/Core/ObserverAction.hpp"
#include "../../../include/TimberWolf/Core/SingleObservable.hpp"

#include "TestObserver.hpp"

namespace twt {
class TestSingleObservable : public tw::SingleObservable<TestObserver> {

public:

    TestSingleObservable () = default;
    ~TestSingleObservable () = default;

    TestSingleObservable (TestSingleObservable&&) = default;
    TestSingleObservable& operator = (TestSingleObservable&&) = default;

    TestSingleObservable (const TestSingleObservable&) = default;
    TestSingleObservable& operator = (const TestSingleObservable&) = default;

    void notifyValue (int);

};
}

#endif
