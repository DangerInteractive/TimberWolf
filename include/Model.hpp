#ifndef H_TW_MODEL
#define H_TW_MODEL

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
