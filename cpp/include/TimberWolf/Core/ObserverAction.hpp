#ifndef TW_CLASS_OBSERVERACTION
#define TW_CLASS_OBSERVERACTION

#include <functional>

namespace tw {
template <class T>
using ObserverAction = std::function<void(T*)>;
}

#endif
