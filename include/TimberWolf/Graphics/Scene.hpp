#ifndef TW_CLASS_SCENE
#define TW_CLASS_SCENE

/**
 * @file
 *
 * Header file for the tw::Scene class.
 */

#include <memory>
#include <vector>

#include "Puppet.hpp"

namespace tw {
class Scene {

public:

    Scene () = default;;
    ~Scene () = default;

    Scene (Scene&&) = default;
    Scene& operator = (Scene&&) = default;

    Scene (const Scene&) = default;
    Scene& operator = (const Scene&) = default;

    unsigned int getPuppetCount () const;
    const std::vector<std::shared_ptr<Puppet>>& getPuppets () const;
    Puppet* getPuppet (unsigned int) const;

    void addPuppets (std::shared_ptr<Puppet>...);
    void setPuppet (unsigned int, std::shared_ptr<Puppet>);

    void clearPuppets ();

private:

    std::vector<std::shared_ptr<Puppet>> m_puppets {};

};
}

#endif
