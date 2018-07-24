#ifndef TW_CLASS_ENTITY
#define TW_CLASS_ENTITY

namespace tw {
class Entity {

public:

    Entity () = default;
    ~Entity () = default;

    Entity (Entity&&) = default;
    Entity& operator = (Entity&&) = default;

    Entity (const Entity&) = default;
    Entity& operator = (const Entity&) = default;

    void update (double);

private:

};
}

#endif
