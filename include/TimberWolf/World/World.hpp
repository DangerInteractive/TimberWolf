#ifndef TW_CLASS_WORLD
#define TW_CLASS_WORLD

namespace tw {
class World {

public:

    World () = default;
    ~World () = default;

    World (World&&) = default;
    World& operator = (World&&) = default;

    World (const World&) = default;
    World& operator = (const World&) = default;

private:

};
}

#endif
