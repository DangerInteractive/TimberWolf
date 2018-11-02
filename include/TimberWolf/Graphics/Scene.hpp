#ifndef TW_CLASS_SCENE
#define TW_CLASS_SCENE

/**
 * @file
 *
 * Header file for the tw::Scene class.
 */

#include <vector>

#include "Camera.hpp"
#include "Light.hpp"
#include "Model.hpp"

namespace tw {
class Scene {

public:

    Scene () = default;;
    ~Scene () = default;

    Scene (Scene&&) = default;
    Scene& operator = (Scene&&) = default;

    Scene (const Scene&) = default;
    Scene& operator = (const Scene&) = default;

    unsigned int getModelCount () const;
    std::vector<Model>& getModels ();
    Model& getModel (unsigned int);

    void addModels (const Model&...);
    void setModel (unsigned int, const Model&);
    void clearModels ();

    void addLights (const Light&...);
    void setLight (unsigned int, const Light&);
    void clearLights ();

private:

    std::vector<Model> m_models {};
    std::vector<Light> m_lights {};
    std::vector<Camera> m_cameras {};

};
}

#endif
