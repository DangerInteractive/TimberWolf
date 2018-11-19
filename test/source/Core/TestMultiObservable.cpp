#include "../../include/Core/TestMultiObservable.hpp"

void twt::TestMultiObservable::testNotify (const tw::ObserverAction<TestObserver>& action) {

    notifyObservers(action);

}
