#include "../../include/Core/TestMultiObservable.hpp"

void twt::TestMultiObservable::notifyValue (int value) {

    notifyObservers([value] (TestObserver* observer) {
        observer->onTestNotification(value);
    });

}
