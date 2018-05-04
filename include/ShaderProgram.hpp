#ifndef H_TW_SHADERPROGRAM
#define H_TW_SHADERPROGRAM

#include <memory>
#include <array>
#include "Shader.hpp"
#include "VertexShader.hpp"
#include "FragmentShader.hpp"
#include "GeometryShader.hpp"
#include "TesselationEvaluationShader.hpp"
#include "TesselationControlShader.hpp"
#include "ComputeShader.hpp"

namespace tw {
class ShaderProgram {

public:

    ShaderProgram () = default;
    ShaderProgram (
        const std::shared_ptr<VertexShader>& = nullptr,
        const std::shared_ptr<FragmentShader>& = nullptr,
        const std::shared_ptr<GeometryShader>& = nullptr,
        const std::shared_ptr<TesselationEvaluationShader>& = nullptr,
        const std::shared_ptr<TesselationControlShader>& = nullptr,
        const std::shared_ptr<ComputeShader>& = nullptr
    );
    ~ShaderProgram () = default;

    ShaderProgram (ShaderProgram&&) = default;
    ShaderProgram& operator = (ShaderProgram&&) = default;

    ShaderProgram (const ShaderProgram&) = delete; // not copyable
    ShaderProgram& operator = (const ShaderProgram&) = default;

    GLuint getId () const;
    bool isLinked () const;

    std::shared_ptr<VertexShader> getVertexShader () const;
    std::shared_ptr<FragmentShader> getFragmentShader () const;
    std::shared_ptr<GeometryShader> getGeometryShader () const;
    std::shared_ptr<TesselationEvaluationShader> getTesselationEvaluationShader () const;
    std::shared_ptr<TesselationControlShader> getTesselationControlShader () const;
    std::shared_ptr<ComputeShader> getComputeShader () const;

    bool setVertexShader (const std::shared_ptr<VertexShader>&);
    bool setFragmentShader (const std::shared_ptr<FragmentShader>&);
    bool setGeometryShader (const std::shared_ptr<GeometryShader>&);
    bool setTesselationEvaluationShader (const std::shared_ptr<TesselationEvaluationShader>&);
    bool setTesselationControlShader (const std::shared_ptr<TesselationControlShader>&);
    bool setComputeShader (const std::shared_ptr<ComputeShader>&);

    bool link ();
    bool use ();
    static bool unuse ();

private:

    GLuint m_id {0};
    bool m_linked {false};

    std::shared_ptr<VertexShader> m_vertexShader {nullptr};
    std::shared_ptr<FragmentShader> m_fragmentShader {nullptr};
    std::shared_ptr<GeometryShader> m_geometryShader {nullptr};
    std::shared_ptr<TesselationEvaluationShader> m_tesselationEvaluationShader {nullptr};
    std::shared_ptr<TesselationControlShader> m_tesselationControlShader {nullptr};
    std::shared_ptr<ComputeShader> m_computeShader {nullptr};

};
}

#endif
