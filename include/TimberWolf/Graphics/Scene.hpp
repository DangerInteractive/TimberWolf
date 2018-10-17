#ifndef TW_CLASS_SCENE
#define TW_CLASS_SCENE

/**
 * @file
 *
 * Header file for the tw::Scene class.
 */

#include <vector>

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

private:

    std::vector<Model> m_models {};

};
}

#endif
