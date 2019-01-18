#ifndef TW_CLASS_SINGLEOBSERVABLE
#define TW_CLASS_SINGLEOBSERVABLE

#include <memory>
#include <mutex>

#include "ObserverAction.hpp"

namespace tw {
template <class T>
class SingleObservable {

public:

    SingleObservable () = default;
    virtual ~SingleObservable () = default; // pure virtual class

    SingleObservable (SingleObservable&&) = default;
    SingleObservable& operator = (SingleObservable&&) = default;

    SingleObservable (const SingleObservable&) = default;
    SingleObservable& operator = (const SingleObservable&) = default;

    T* getObserver () {
        return m_observer.get();
    }

    virtual void setObserver (std::unique_ptr<T>&& observer) {
        auto lock = getLock();
        m_observer = std::move(observer);
    }

    void setObserver (T* observer) {
        setObserver(std::make_unique<T>(observer));
    }

    template <class TSub, typename ...TArg>
    void makeObserver (TArg&&... args) {
        std::unique_ptr<T> observer = std::make_unique<TSub>(std::forward<TArg>(args)...);
        setObserver(std::move(observer));
    }

    void resetObserver () {
        auto lock = getLock();
        m_observer->kill();
        m_observer.reset();
    }

protected:

    void notifyObserver (const ObserverAction<T>& action) {
        auto lock = getLock();
        if (m_observer != nullptr) {
            if (m_observer->isAlive()) {
                action(m_observer.get());
            } else {
                m_observer.reset();
            }
        }
    }

    std::unique_lock<std::mutex> getLock () {
        return std::unique_lock<std::mutex>(m_mutex);
    }

private:

    std::mutex m_mutex {};
    std::unique_ptr<T> m_observer {nullptr};

};
}

#endif
