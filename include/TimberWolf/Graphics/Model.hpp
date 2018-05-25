#ifndef H_TW_MODEL
#define H_TW_MODEL

/**
 * @file
 *
 * Header file for the tw::Model class.
 */

#include <memory>
#include <string>
#include "OpenGL/VertexArray.hpp"
#include "OpenGL/VertexBuffer.hpp"
#include "OpenGL/ShaderStore.hpp"
#include "OpenGL/ShaderProgram.hpp"

namespace tw {
class Model {

public:

    Model () = default;;
    explicit Model (VertexArray&&);
    explicit Model (const std::shared_ptr<VertexArray>&);
    Model (VertexArray&&, const std::shared_ptr<ShaderProgram>&);
    Model (VertexArray&&, const std::string&);
    Model (const std::shared_ptr<VertexArray>&, const std::shared_ptr<ShaderProgram>&);
    Model (const std::shared_ptr<VertexArray>&, const std::string&);
    ~Model () = default;

    Model (Model&&) = default;
    Model& operator = (Model&&) = default;

    Model (const Model&) = default;
    Model& operator = (const Model&) = default;

    std::shared_ptr<VertexArray> getVAO () const;
    std::shared_ptr<ShaderProgram> getShaderProgram() const;
    unsigned int getVertexCount () const;

    void setVAO (VertexArray&&);
    void setVAO (const std::shared_ptr<VertexArray>&);
    void setShaderProgram (const std::shared_ptr<ShaderProgram>&);
    void setShaderProgram (const std::string&);
    void setVertexCount (unsigned int);

private:

    std::shared_ptr<VertexArray> m_vao;
    std::shared_ptr<ShaderProgram> m_shader;
    unsigned int m_vertexCount {0};

};
}

#endif
