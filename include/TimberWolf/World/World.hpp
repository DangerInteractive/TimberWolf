#ifndef TW_CLASS_WORLD
#define TW_CLASS_WORLD

#include <atomic>
#include <memory>
#include <vector>

#include "Entity.hpp"

namespace tw {
class World {

public:

    World () = default;
    ~World () = default;

    World (World&&) = default;
    World& operator = (World&&) = default;

    World (const World&) = default;
    World& operator = (const World&) = default;

    void update (double);

    template <typename T, typename ...TArg>
    T* makeEntity (TArg... args) {
        return m_entities.emplace_back<T>(std::forward<TArg>(args)...).get();
    }
    World& addEntity (std::unique_ptr<Entity>&&);
    World& addEntity (Entity*);

private:

    void preUpdate ();
    void postUpdate ();

    std::atomic<bool> m_running {false};
    std::vector<std::unique_ptr<Entity>> m_entities {};
    std::vector<std::unique_ptr<Entity>> m_pendingEntities {};

};
}

#endif
