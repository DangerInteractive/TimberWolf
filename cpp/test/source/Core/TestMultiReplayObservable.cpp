#include "../../include/Core/TestMultiReplayObservable.hpp"

void twt::TestMultiReplayObservable::notifyValue (int value) {

    notifyObservers([value] (TestObserver* observer) {
        observer->onTestNotification(value);
    });

}

void twt::TestMultiReplayObservable::notifyAndReplayValue (int value) {

    notifyObserversAndReplay([value] (TestObserver* observer) {
        observer->onTestNotification(value);
    });

}
