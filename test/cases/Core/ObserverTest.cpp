#include <catch2/catch.hpp>

#include <memory>

#include "../../include/Core/TestMultiObservable.hpp"
#include "../../include/Core/TestMultiReplayObservable.hpp"
#include "../../include/Core/TestObserver.hpp"
#include "../../include/Core/TestSingleObservable.hpp"
#include "../../include/Core/TestSingleReplayObservable.hpp"

SCENARIO ("Observers can be registered and notified by Observables", "[core][observer]") {

    GIVEN ("a TestSingleObservable given a TestObserver") {
        twt::TestSingleObservable observable;
        twt::TestObserver* observer = new twt::TestObserver();
        observable.setObserver(std::unique_ptr<twt::TestObserver>(observer));

        REQUIRE (observer->wasNotified() == false);
        REQUIRE (observer->getNotifiedValue() == 0);
        REQUIRE (observer == observable.getObserver());

        WHEN ("the observer is notified via the observable") {
            observable.notifyValue(50);

            THEN ("The observer was notified") {
                REQUIRE (observer->wasNotified() == true);
                REQUIRE (observer->getNotifiedValue() == 50);
            }
        }

    }

    GIVEN ("a TestMultiObservable given two TestObservers") {
        twt::TestMultiObservable observable;
        twt::TestObserver* observer1 = new twt::TestObserver();
        twt::TestObserver* observer2 = new twt::TestObserver();
        observable.addObserver(std::unique_ptr<twt::TestObserver>(observer1));
        observable.addObserver(std::unique_ptr<twt::TestObserver>(observer2));

        REQUIRE (observer1->wasNotified() == false);
        REQUIRE (observer1->getNotifiedValue() == 0);
        REQUIRE (observer2->wasNotified() == false);
        REQUIRE (observer2->getNotifiedValue() == 0);

        WHEN ("the observer is notified via the observable") {
            observable.notifyValue(50);

            THEN ("the observers were both notified") {
                REQUIRE (observer1->wasNotified() == true);
                REQUIRE (observer1->getNotifiedValue() == 50);
                REQUIRE (observer2->wasNotified() == true);
                REQUIRE (observer2->getNotifiedValue() == 50);
            }
        }

    }

    GIVEN ("a TestSingleReplayObservable given a TestObserver") {
        twt::TestSingleReplayObservable observable;
        twt::TestObserver* observer = new twt::TestObserver();
        observable.setObserver(std::unique_ptr<twt::TestObserver>(observer));

        REQUIRE (observer->wasNotified() == false);
        REQUIRE (observer->getNotifiedValue() == 0);
        REQUIRE (observer == observable.getObserver());

        WHEN ("the observer is notified via the observable") {
            observable.notifyValue(50);

            THEN ("The observer was notified") {
                REQUIRE (observer->wasNotified() == true);
                REQUIRE (observer->getNotifiedValue() == 50);
            }
        }

    }

    GIVEN ("a TestMultiReplayObservable given two TestObservers") {
        twt::TestMultiReplayObservable observable;
        twt::TestObserver* observer1 = new twt::TestObserver();
        twt::TestObserver* observer2 = new twt::TestObserver();
        observable.addObserver(std::unique_ptr<twt::TestObserver>(observer1));
        observable.addObserver(std::unique_ptr<twt::TestObserver>(observer2));

        REQUIRE (observer1->wasNotified() == false);
        REQUIRE (observer1->getNotifiedValue() == 0);
        REQUIRE (observer2->wasNotified() == false);
        REQUIRE (observer2->getNotifiedValue() == 0);

        WHEN ("the observer is notified via the observable") {
            observable.notifyValue(50);

            THEN ("the observers were both notified") {
                REQUIRE (observer1->wasNotified() == true);
                REQUIRE (observer1->getNotifiedValue() == 50);
                REQUIRE (observer2->wasNotified() == true);
                REQUIRE (observer2->getNotifiedValue() == 50);
            }
        }

    }

}
