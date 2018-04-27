#ifndef H_TW_FRAGMENTSHADER
#define H_TW_FRAGMENTSHADER

#include <string>
#include "Shader.hpp"

namespace tw {
class FragmentShader : public Shader {

public:

    FragmentShader ();
    explicit FragmentShader (const std::string&);
    ~FragmentShader () = default;

    FragmentShader (FragmentShader&&) = default;
    FragmentShader& operator = (FragmentShader&&) = default;

    FragmentShader (const FragmentShader&) = delete; // not copyable
    FragmentShader& operator = (const FragmentShader&) = delete;

};
}

#endif
