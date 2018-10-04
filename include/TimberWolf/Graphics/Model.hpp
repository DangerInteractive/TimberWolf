#ifndef TW_CLASS_MODEL
#define TW_CLASS_MODEL

/**
 * @file
 *
 * Header file for the tw::Model class.
 */

#include <memory>
#include <string>
#include "OpenGL/GLVertexArray.hpp" // TODO: decouple OpenGL from here
#include "OpenGL/GLVertexBuffer.hpp"
#include "OpenGL/GLShaderProgram.hpp"

namespace tw {
class Model {

public:

    Model () = default;;
    explicit Model (GLVertexArray&&);
    explicit Model (const std::shared_ptr<GLVertexArray>&);
    Model (GLVertexArray&&, const std::shared_ptr<GLShaderProgram>&);
    Model (const std::shared_ptr<GLVertexArray>&, const std::shared_ptr<GLShaderProgram>&);
    ~Model () = default;

    Model (Model&&) = default;
    Model& operator = (Model&&) = default;

    Model (const Model&) = default;
    Model& operator = (const Model&) = default;

    std::shared_ptr<GLVertexArray> getVAO () const;
    std::shared_ptr<GLShaderProgram> getShaderProgram() const; // TODO: decouple OpenGL from here
    unsigned int getVertexCount () const;

    void setVAO (GLVertexArray&&);
    void setVAO (const std::shared_ptr<GLVertexArray>&);
    void setShaderProgram (const std::shared_ptr<GLShaderProgram>&);
    void setVertexCount (unsigned int);

private:

    std::shared_ptr<GLVertexArray> m_vao;
    std::shared_ptr<GLShaderProgram> m_shader;
    unsigned int m_vertexCount {0};

};
}

#endif
