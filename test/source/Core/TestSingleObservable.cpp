#include "../../include/Core/TestSingleObservable.hpp"

void twt::TestSingleObservable::testNotify (const tw::ObserverAction<TestObserver>& action) {

    notifyObserver(action);

}
