#ifndef TW_CLASS_ENTITYCOMPONENT
#define TW_CLASS_ENTITYCOMPONENT

namespace tw { class Entity; }

namespace tw {
class EntityComponent {

public:

    EntityComponent () = default;
    explicit EntityComponent (Entity*);
    virtual ~EntityComponent () = default;

    EntityComponent (EntityComponent&&) = default;
    EntityComponent& operator = (EntityComponent&&) = default;

    EntityComponent (const EntityComponent&) = default;
    EntityComponent& operator = (const EntityComponent&) = default;

    virtual void update (double) = 0;

    Entity* getEntity();

    EntityComponent& attachToEntity (Entity*);
    EntityComponent& detach ();

private:

    Entity* m_entity {nullptr};

};
}

#endif
