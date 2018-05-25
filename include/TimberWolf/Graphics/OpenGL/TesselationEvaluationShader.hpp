#ifndef H_TW_TESSELATIONEVALUATIONSHADER
#define H_TW_TESSELATIONEVALUATIONSHADER

/**
 * @file
 *
 * Header file for the tw::TesselationEvaluationShader class.
 */

#include <string>
#include "Shader.hpp"

namespace tw {
class TesselationEvaluationShader : public Shader {

public:

    TesselationEvaluationShader ();
    explicit TesselationEvaluationShader (const std::string&);
    ~TesselationEvaluationShader () = default;

    TesselationEvaluationShader (TesselationEvaluationShader&&) = default;
    TesselationEvaluationShader& operator = (TesselationEvaluationShader&&) = default;

    TesselationEvaluationShader (const TesselationEvaluationShader&) = delete; // not copyable
    TesselationEvaluationShader& operator = (const TesselationEvaluationShader&) = delete;

};
}

#endif
