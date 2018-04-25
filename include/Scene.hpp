#ifndef H_TW_SCENE
#define H_TW_SCENE

#include <vector>
#include "Model.hpp"

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

    std::vector<Model> m_models;

};
}

#endif
