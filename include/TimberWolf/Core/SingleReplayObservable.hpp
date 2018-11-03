#ifndef TW_CLASS_SINGLEREPLAYOBSERVABLE
#define TW_CLASS_SINGLEREPLAYOBSERVABLE

#include <memory>
#include <mutex>
#include <vector>

#include "ObserverAction.hpp"
#include "SingleObservable.hpp"

namespace tw {
template <class T>
class SingleReplayObservable : public SingleObservable<T> {

public:

    SingleReplayObservable () = default;
    virtual ~SingleReplayObservable () = 0; // pure virtual class

    SingleReplayObservable (SingleReplayObservable&&) = default;
    SingleReplayObservable& operator = (SingleReplayObservable&&) = default;

    SingleReplayObservable (const SingleReplayObservable&) = default;
    SingleReplayObservable& operator = (const SingleReplayObservable&) = default;

    virtual void setObserver (std::unique_ptr<T>&& observer) override {
        auto lock = this->getLock();
        if (observer != nullptr) {
            for (auto action : m_replays) {
                action(observer.get());
            }
        }
        lock.release();
        SingleObservable<T>::setObserver(std::move(observer));
    }

protected:

    void notifyObserverAndReplay (ObserverAction<T> action) {
        this->notifyObserver(action);
        m_replays.emplace_back(std::move(action));
    }

    void notifyObserverAndReplay (ObserverAction<T>&& action) {
        this->notifyObserver(action);
        m_replays.emplace_back(std::move(action));
    }

    void resetReplays () {
        (std::vector<ObserverAction<T>>()).swap(m_replays);
    }

private:

    std::vector<ObserverAction<T>> m_replays {};

};
}

#endif
