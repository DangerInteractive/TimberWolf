#include "../../include/Core/TestSingleReplayObservable.hpp"

void twt::TestSingleReplayObservable::notifyValue (int value) {

    notifyObserver([value] (TestObserver* observer) {
        observer->onTestNotification(value);
    });

}

void twt::TestSingleReplayObservable::notifyAndReplayValue (int value) {

    notifyObserverAndReplay([value] (TestObserver* observer) {
        observer->onTestNotification(value);
    });

}
