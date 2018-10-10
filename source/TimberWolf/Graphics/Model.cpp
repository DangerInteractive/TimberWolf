#include "../../../include/TimberWolf/Graphics/Model.hpp"

/**
 * @class tw::Model
 *
 * Representation of a three dimensional model, to be rendered by tw::Renderer.
 * It stores a handle to an OpenGL VAO (vertex array object) containing the
 * vertex, index, and texture buffers, a count of vertices in the VAO, and a
 * handle to an OpenGL shader program to use while the object is being rendered.
 */

unsigned int tw::Model::getFragmentCount () const {

    return m_fragments.size();

}

const tw::ModelFragment& tw::Model::getFragment (unsigned int index) const {

    return m_fragments.at(index);

}

unsigned int tw::Model::addFragment (ModelFragment&& fragment) {

    m_fragments.emplace_back(std::move(fragment));
    return m_fragments.size() - 1;

}

unsigned int tw::Model::addFragment (const ModelFragment& fragment) {

    ModelFragment frag = fragment;
    return addFragment(std::move(frag));

}
