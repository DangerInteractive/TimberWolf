#ifndef H_TW_MODEL
#define H_TW_MODEL

#include <memory>
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

namespace tw {
class Model {

public:

    Model () = default;;
    explicit Model (VertexArray&&);
    explicit Model (const std::shared_ptr<VertexArray>&);
    ~Model () = default;

    Model (Model&&) = default;
    Model& operator = (Model&&) = default;

    Model (const Model&) = default;
    Model& operator = (const Model&) = default;

    std::shared_ptr<VertexArray> getVAO () const;
    unsigned int getVertexCount () const;

    void setVAO (VertexArray&&);
    void setVAO (const std::shared_ptr<VertexArray>&);
    void setVertexCount (unsigned int);

private:

    std::shared_ptr<VertexArray> m_vao;
    unsigned int m_vertexCount {0};

};
}

#endif
