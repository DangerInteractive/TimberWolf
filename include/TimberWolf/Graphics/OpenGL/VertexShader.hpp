#ifndef H_TW_VERTEXSHADER
#define H_TW_VERTEXSHADER

/**
 * @file
 *
 * Header file for the tw::VertexShader class.
 */

#include <string>
#include "Shader.hpp"

namespace tw {
class VertexShader : public Shader {

public:

    VertexShader ();
    explicit VertexShader (const std::string&);
    ~VertexShader () = default;

    VertexShader (VertexShader&&) = default;
    VertexShader& operator = (VertexShader&&) = default;

    VertexShader (const VertexShader&) = delete; // not copyable
    VertexShader& operator = (const VertexShader&) = delete;

};
}

#endif
