#ifndef TW_CLASS_GLMATERIALHANDLE
#define TW_CLASS_GLMATERIALHANDLE

#include <memory>

#include "../Material.hpp"
#include "../MaterialHandle.hpp"

#include "GLFragmentShader.hpp"
#include "GLShaderProgram.hpp"
#include "GLVertexShader.hpp"

namespace tw {
class GLMaterialHandle : public MaterialHandle {

public:

    GLMaterialHandle () = default;
    explicit GLMaterialHandle (GLShaderProgram&&);
    explicit GLMaterialHandle (Material&);
    ~GLMaterialHandle () = default;

    GLMaterialHandle (GLMaterialHandle&&) = default;
    GLMaterialHandle& operator = (GLMaterialHandle&&) = default;

    GLMaterialHandle (const GLMaterialHandle&) = default;
    GLMaterialHandle& operator = (const GLMaterialHandle&) = default;

    const GLShaderProgram& getShaderProgram () const;

    bool bind () override;
    bool unbind () override;

    static bool clearBound ();

    void init ();

private:

    GLShaderProgram m_shaderProgram {};

    static std::weak_ptr<GLVertexShader> m_vert;
    static std::weak_ptr<GLFragmentShader> m_frag;

};
}

#endif
