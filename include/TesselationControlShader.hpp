#ifndef H_TW_TESSELATIONCONTROLSHADER
#define H_TW_TESSELATIONCONTROLSHADER

#include <string>
#include "Shader.hpp"

namespace tw {
class TesselationControlShader : public Shader {

public:

    TesselationControlShader ();
    explicit TesselationControlShader (const std::string&);
    ~TesselationControlShader () = default;

    TesselationControlShader (TesselationControlShader&&) = default;
    TesselationControlShader& operator = (TesselationControlShader&&) = default;

    TesselationControlShader (const TesselationControlShader&) = default;
    TesselationControlShader& operator = (const TesselationControlShader&) = default;

};
}

#endif
