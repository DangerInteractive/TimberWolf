#include "../../include/Core/TestSingleReplayObservable.hpp"

void twt::TestSingleReplayObservable::testNotify (const tw::ObserverAction<TestObserver>& action) {

    notifyObserver(action);

}

void twt::TestSingleReplayObservable::testNotifyAndReplay (const tw::ObserverAction<TestObserver>& action) {

    notifyObserverAndReplay(action);

}
