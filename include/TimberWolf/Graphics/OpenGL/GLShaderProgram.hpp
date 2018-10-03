#ifndef TW_CLASS_SHADERPROGRAM
#define TW_CLASS_SHADERPROGRAM

/**
 * @file
 *
 * Header file for the tw::GLShaderProgram class.
 */

#include <memory>
#include <array>

#include "../MaterialHandle.hpp"

#include "GLShader.hpp"
#include "GLVertexShader.hpp"
#include "GLFragmentShader.hpp"
#include "GLGeometryShader.hpp"
#include "GLTesselationEvaluationShader.hpp"
#include "GLTesselationControlShader.hpp"
#include "GLComputeShader.hpp"

namespace tw {
class GLShaderProgram : public MaterialHandle {

public:

    GLShaderProgram ();
    GLShaderProgram (
        const std::shared_ptr<GLVertexShader>& = nullptr,
        const std::shared_ptr<GLFragmentShader>& = nullptr,
        const std::shared_ptr<GLGeometryShader>& = nullptr,
        const std::shared_ptr<GLTesselationEvaluationShader>& = nullptr,
        const std::shared_ptr<GLTesselationControlShader>& = nullptr,
        const std::shared_ptr<GLComputeShader>& = nullptr
    );
    ~GLShaderProgram () = default;

    GLShaderProgram (GLShaderProgram&&) = default;
    GLShaderProgram& operator = (GLShaderProgram&&) = default;

    GLShaderProgram (const GLShaderProgram&) = delete; // not copyable
    GLShaderProgram& operator = (const GLShaderProgram&) = default;

    GLuint getId () const;
    bool isLinked () const;

    std::shared_ptr<GLVertexShader> getVertexShader () const;
    std::shared_ptr<GLFragmentShader> getFragmentShader () const;
    std::shared_ptr<GLGeometryShader> getGeometryShader () const;
    std::shared_ptr<GLTesselationEvaluationShader> getTesselationEvaluationShader () const;
    std::shared_ptr<GLTesselationControlShader> getTesselationControlShader () const;
    std::shared_ptr<GLComputeShader> getComputeShader () const;

    bool setVertexShader (const std::shared_ptr<GLVertexShader>&);
    bool setFragmentShader (const std::shared_ptr<GLFragmentShader>&);
    bool setGeometryShader (const std::shared_ptr<GLGeometryShader>&);
    bool setTesselationEvaluationShader (const std::shared_ptr<GLTesselationEvaluationShader>&);
    bool setTesselationControlShader (const std::shared_ptr<GLTesselationControlShader>&);
    bool setComputeShader (const std::shared_ptr<GLComputeShader>&);

    bool link ();

    bool bind ();
    bool unbind ();
    static void clearBound ();

private:

    GLuint m_id {0};
    bool m_linked {false};

    std::shared_ptr<GLVertexShader> m_vertexShader {nullptr};
    std::shared_ptr<GLFragmentShader> m_fragmentShader {nullptr};
    std::shared_ptr<GLGeometryShader> m_geometryShader {nullptr};
    std::shared_ptr<GLTesselationEvaluationShader> m_tesselationEvaluationShader {nullptr};
    std::shared_ptr<GLTesselationControlShader> m_tesselationControlShader {nullptr};
    std::shared_ptr<GLComputeShader> m_computeShader {nullptr};

};
}

#endif
