#ifndef TW_CLASS_MULTIREPLAYOBSERVABLE
#define TW_CLASS_MULTIREPLAYOBSERVABLE

#include <memory>
#include <mutex>
#include <vector>

#include "ObserverAction.hpp"
#include "MultiObservable.hpp"

namespace tw {
template <class T>
class MultiReplayObservable : public MultiObservable<T> {

public:

    MultiReplayObservable () = default;
    virtual ~MultiReplayObservable () = default; // pure virtual class

    MultiReplayObservable (MultiReplayObservable&&) = default;
    MultiReplayObservable& operator = (MultiReplayObservable&&) = default;

    MultiReplayObservable (const MultiReplayObservable&) = default;
    MultiReplayObservable& operator = (const MultiReplayObservable&) = default;

    virtual void addObserver (std::unique_ptr<T>&& observer) override {
        if (observer != nullptr) {
            for (auto action : m_replays) {
                action(observer.get());
            }
        }
        MultiObservable<T>::addObserver(std::move(observer));
    }

protected:

    void notifyObserversAndReplay (ObserverAction<T> action) {
        this->notifyObservers(action);
        m_replays.emplace_back(std::move(action));
    }

    void notifyObserversAndReplay (ObserverAction<T>&& action) && {
        this->notifyObservers(action);
        m_replays.emplace_back(std::move(action));
    }

private:

    std::vector<ObserverAction<T>> m_replays {};

};
}

#endif
