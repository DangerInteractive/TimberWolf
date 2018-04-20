#ifndef H_CLASS_MODEL
#define H_CLASS_MODEL

#include <memory>
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

namespace tw {
class Model {

public:

    Model ();
    ~Model () = default;

    Model (Model&&) = default;
    Model& operator = (Model&&) = default;

    Model (const Model&) = default;
    Model& operator = (const Model&) = default;

private:

    std::shared_ptr<VertexArray> m_vao;

};
}

#endif
