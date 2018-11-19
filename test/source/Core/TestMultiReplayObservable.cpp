#include "../../include/Core/TestMultiReplayObservable.hpp"

void twt::TestMultiReplayObservable::testNotify (const tw::ObserverAction<TestObserver>& action) {

    notifyObservers(action);

}

void twt::TestMultiReplayObservable::testNotifyAndReplay (const tw::ObserverAction<TestObserver>& action) {

    notifyObserversAndReplay(action);

}
