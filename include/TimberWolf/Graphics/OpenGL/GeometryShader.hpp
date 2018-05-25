#ifndef H_TW_GEOMETRYSHADER
#define H_TW_GEOMETRYSHADER

/**
 * @file
 *
 * Header file for the tw::GeometryShader class.
 */

#include <string>
#include "Shader.hpp"

namespace tw {
class GeometryShader : public Shader {

public:

    GeometryShader ();
    explicit GeometryShader (const std::string&);
    ~GeometryShader () = default;

    GeometryShader (GeometryShader&&) = default;
    GeometryShader& operator = (GeometryShader&&) = default;

    GeometryShader (const GeometryShader&) = delete; // not copyable
    GeometryShader& operator = (const GeometryShader&) = delete;

};
}

#endif
