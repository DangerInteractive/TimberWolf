#ifndef TW_CLASS_SCENE
#define TW_CLASS_SCENE

/**
 * @file
 *
 * Header file for the tw::Scene class.
 */

#include <memory>
#include <vector>

namespace tw {
class Scene {

public:

    Scene ();
    ~Scene () = default;

    Scene (Scene&&) = default;
    Scene& operator = (Scene&&) = default;

    Scene (const Scene&) = default;
    Scene& operator = (const Scene&) = default;

private:

};
}

#endif
