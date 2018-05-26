#ifndef H_TW_GLTESSELATIONEVALUATIONSHADER
#define H_TW_GLTESSELATIONEVALUATIONSHADER

/**
 * @file
 *
 * Header file for the tw::GLTesselationEvaluationShader class.
 */

#include <string>
#include "GLShader.hpp"

namespace tw {
class GLTesselationEvaluationShader : public GLShader {

public:

    GLTesselationEvaluationShader ();
    explicit GLTesselationEvaluationShader (const std::string&);
    ~GLTesselationEvaluationShader () = default;

    GLTesselationEvaluationShader (GLTesselationEvaluationShader&&) = default;
    GLTesselationEvaluationShader& operator = (GLTesselationEvaluationShader&&) = default;

    GLTesselationEvaluationShader (const GLTesselationEvaluationShader&) = delete; // not copyable
    GLTesselationEvaluationShader& operator = (const GLTesselationEvaluationShader&) = delete;

};
}

#endif
