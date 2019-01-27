#ifndef TW_CLASS_MULTIOBSERVABLE
#define TW_CLASS_MULTIOBSERVABLE

#include <memory>
#include <mutex>
#include <vector>

#include "ObserverAction.hpp"

namespace tw {
template <class T>
class MultiObservable {

public:

    MultiObservable () = default;
    virtual ~MultiObservable () = default; // pure virtual class

    MultiObservable (MultiObservable&&) = default;
    MultiObservable& operator = (MultiObservable&&) = default;

    MultiObservable (const MultiObservable&) = default;
    MultiObservable& operator = (const MultiObservable&) = default;

    virtual void addObserver (std::unique_ptr<T>&& newObserver) {
        auto lock = getLock();
        for (auto observer = m_observers.begin(); observer != m_observers.end(); ++observer) {
            if (*observer == nullptr) {
                *observer = std::move(newObserver);
                return;
            }
        }
        m_observers.emplace_back(std::move(newObserver));
    }

    void addObserver (T* observer) {
        addObserver(std::make_unique<T>(observer));
    }

    template <class TSub, typename ...TArg>
    void makeObserver (TArg&&... args) {
        std::unique_ptr<T> observer = std::make_unique<TSub>(std::forward<TArg>(args)...);
        setObserver(std::move(observer));
    }

    void resetObservers () {
        auto lock = getLock();
        for (auto observer = m_observers.begin(); observer != m_observers.end(); ++observer) {
            (*observer)->kill();
            observer->reset();
        }
        (std::vector<std::unique_ptr<T>>()).swap(m_observers);
    }

protected:

    void notifyObservers (const ObserverAction<T>& action) {
        auto lock = getLock();
        for (auto observer = m_observers.begin(); observer != m_observers.end(); ++observer) {
            if (*observer != nullptr) {
                if ((*observer)->isAlive()) {
                    action(observer->get());
                } else {
                    observer->reset();
                }
            }
        }
    }

    std::unique_lock<std::mutex> getLock () {
        return std::unique_lock<std::mutex>(m_mutex);
    }

private:

    std::mutex m_mutex {};
    std::vector<std::unique_ptr<T>> m_observers {};

};
}

#endif
