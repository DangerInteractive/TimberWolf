#ifndef H_TW_COMPUTESHADER
#define H_TW_COMPUTESHADER

/**
 * @file
 *
 * Header file for the tw::ComputeShader class.
 */

#include <string>
#include "Shader.hpp"

namespace tw {
class ComputeShader : public Shader {

public:

    ComputeShader ();
    explicit ComputeShader (const std::string&);
    ~ComputeShader () = default;

    ComputeShader (ComputeShader&&) = default;
    ComputeShader& operator = (ComputeShader&&) = default;

    ComputeShader (const ComputeShader&) = delete; // not copyable
    ComputeShader& operator = (const ComputeShader&) = delete;

};
}

#endif
