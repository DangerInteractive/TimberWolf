#include "../../include/Core/TestSingleObservable.hpp"

void twt::TestSingleObservable::notifyValue (int value) {

    notifyObserver([value] (TestObserver* observer) {
        observer->onTestNotification(value);
    });

}
