#ifndef TW_CLASS_MODEL
#define TW_CLASS_MODEL

/**
 * @file
 *
 * Header file for the tw::Model class.
 */

#include <vector>

#include "ModelFragment.hpp"

namespace tw {
class Model {

public:

    Model () = default;
    ~Model () = default;

    Model (Model&&) = default;
    Model& operator = (Model&&) = default;

    Model (const Model&) = default;
    Model& operator = (const Model&) = default;

    unsigned int getFragmentCount () const;
    const ModelFragment& getFragment (unsigned int) const;
    unsigned int addFragment (ModelFragment&&);
    unsigned int addFragment (const ModelFragment&);

private:

    std::vector<ModelFragment> m_fragments {};

};
}

#endif
