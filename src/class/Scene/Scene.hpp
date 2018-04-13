#ifndef H_CLASS_SCENE
#define H_CLASS_SCENE

#include <vector>
#include "../Model/Model.hpp"

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
