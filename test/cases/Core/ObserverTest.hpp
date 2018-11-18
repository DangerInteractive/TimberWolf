#include <catch2/catch.hpp>

#include <memory>

#include "../../../include/TimberWolf/Core/Observer.hpp"
#include "../../../include/TimberWolf/Core/ObserverAction.hpp"
#include "../../../include/TimberWolf/Core/MultiObservable.hpp"
#include "../../../include/TimberWolf/Core/MultiReplayObservable.hpp"
#include "../../../include/TimberWolf/Core/SingleObservable.hpp"
#include "../../../include/TimberWolf/Core/SingleReplayObservable.hpp"

class TestObserver : public tw::Observer {

public:

    TestObserver () = default;
    ~TestObserver () = default;

    TestObserver (TestObserver&&) = default;
    TestObserver& operator = (TestObserver&&) = default;

    TestObserver (const TestObserver&) = default;
    TestObserver& operator = (const TestObserver&) = default;

    bool wasNotified () {
        return m_notified;
    }

    virtual void onTestNotification () {
        m_notified = true;
    }

private:

    bool m_notified {false};

};

class TestSingleObservable : public tw::SingleObservable<TestObserver> {

public:

    TestSingleObservable () = default;
    ~TestSingleObservable () = default;

    TestSingleObservable (TestSingleObservable&&) = default;
    TestSingleObservable& operator = (TestSingleObservable&&) = default;

    TestSingleObservable (const TestSingleObservable&) = default;
    TestSingleObservable& operator = (const TestSingleObservable&) = default;

    void testNotify (const tw::ObserverAction<TestObserver>& action) {
        notifyObserver(action);
    }

};

class TestMultiObservable : public tw::MultiObservable<TestObserver> {

public:

    TestMultiObservable () = default;
    ~TestMultiObservable () = default;

    TestMultiObservable (TestMultiObservable&&) = default;
    TestMultiObservable& operator = (TestMultiObservable&&) = default;

    TestMultiObservable (const TestMultiObservable&) = default;
    TestMultiObservable& operator = (const TestMultiObservable&) = default;

    void testNotify (const tw::ObserverAction<TestObserver>& action) {
        notifyObservers(action);
    }

};

class TestSingleReplayObservable : public tw::SingleReplayObservable<TestObserver> {

public:

    TestSingleReplayObservable () = default;
    ~TestSingleReplayObservable () = default;

    TestSingleReplayObservable (TestSingleReplayObservable&&) = default;
    TestSingleReplayObservable& operator = (TestSingleReplayObservable&&) = default;

    TestSingleReplayObservable (const TestSingleReplayObservable&) = default;
    TestSingleReplayObservable& operator = (const TestSingleReplayObservable&) = default;

    void testNotify (const tw::ObserverAction<TestObserver>& action) {
        notifyObserver(action);
    }

    void testNotifyAndReplay (const tw::ObserverAction<TestObserver>& action) {
        notifyObserverAndReplay(action);
    }

};

class TestMultiReplayObservable : public tw::MultiReplayObservable<TestObserver> {

public:

    TestMultiReplayObservable () = default;
    ~TestMultiReplayObservable () = default;

    TestMultiReplayObservable (TestMultiReplayObservable&&) = default;
    TestMultiReplayObservable& operator = (TestMultiReplayObservable&&) = default;

    TestMultiReplayObservable (const TestMultiReplayObservable&) = default;
    TestMultiReplayObservable& operator = (const TestMultiReplayObservable&) = default;

    void testNotify (const tw::ObserverAction<TestObserver>& action) {
        notifyObservers(action);
    }

    void testNotifyAndReplay (const tw::ObserverAction<TestObserver>& action) {
        notifyObserversAndReplay(action);
    }

};

SCENARIO ("Observers can be registered and notified by Observables", "[core][observer]") {

    GIVEN ("a default constructed TestSingleObservable given a TestObserver") {
        TestSingleObservable observable;
        TestObserver* observer = new TestObserver();
        observable.setObserver(std::unique_ptr<TestObserver>(observer));

        REQUIRE (observer->wasNotified() == false);
        REQUIRE (observer == observable.getObserver());

        WHEN ("the observer is notified via the observable") {
            observable.testNotify([] (TestObserver* observer) {
                observer->onTestNotification();
            });

            THEN ("The observer was notified") {
                REQUIRE (observer->wasNotified() == true);
            }
        }

    }

    GIVEN ("a TestMultiObservable given two TestObservers") {
        TestMultiObservable observable;
        TestObserver* observer1 = new TestObserver();
        TestObserver* observer2 = new TestObserver();
        observable.addObserver(std::unique_ptr<TestObserver>(observer1));
        observable.addObserver(std::unique_ptr<TestObserver>(observer2));

        REQUIRE (observer1->wasNotified() == false);
        REQUIRE (observer2->wasNotified() == false);

        WHEN ("the observer is notified via the observable") {
            observable.testNotify([] (TestObserver* observer) {
                observer->onTestNotification();
            });

            THEN ("the observers were both notified") {
                REQUIRE (observer1->wasNotified() == true);
                REQUIRE (observer2->wasNotified() == true);
            }
        }

    }

    GIVEN ("a TestSingleReplayObservable given a TestObserver") {
        TestSingleReplayObservable observable;
        TestObserver* observer = new TestObserver();
        observable.setObserver(std::unique_ptr<TestObserver>(observer));

        REQUIRE (observer->wasNotified() == false);
        REQUIRE (observer == observable.getObserver());

        WHEN ("the observer is notified via the observable") {
            observable.testNotify([] (TestObserver* observer) {
                observer->onTestNotification();
            });

            THEN ("The observer was notified") {
                REQUIRE (observer->wasNotified() == true);
            }
        }

    }

    GIVEN ("a TestMultiReplayObservable given two TestObservers") {
        TestMultiReplayObservable observable;
        TestObserver* observer1 = new TestObserver();
        TestObserver* observer2 = new TestObserver();
        observable.addObserver(std::unique_ptr<TestObserver>(observer1));
        observable.addObserver(std::unique_ptr<TestObserver>(observer2));

        REQUIRE (observer1->wasNotified() == false);
        REQUIRE (observer2->wasNotified() == false);

        WHEN ("the observer is notified via the observable") {
            observable.testNotify([] (TestObserver* observer) {
                observer->onTestNotification();
            });

            THEN ("the observers were both notified") {
                REQUIRE (observer1->wasNotified() == true);
                REQUIRE (observer2->wasNotified() == true);
            }
        }

    }

}
