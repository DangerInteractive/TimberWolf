#ifndef H_TW_SHADER
#define H_TW_SHADER

/**
 * @file
 *
 * Header file for the tw::Shader class.
 */

#include <string>
#include <array>
#include <GL/glew.h>
#include "../../Log/Log.hpp"

namespace tw {
class Shader {

public:

    Shader () = delete; // parent class only
    virtual ~Shader ();

    Shader (Shader&&) = default;
    Shader& operator = (Shader&&) = default;

    Shader (const Shader&) = delete; // not copyable
    Shader& operator = (const Shader&) = delete;

    GLenum getType () const;
    GLuint getId () const;
    std::string getSource () const;
    bool isCompiled () const;

    bool setSource (const std::string&);

    bool compile ();

protected:

    explicit Shader (GLenum);
    Shader (GLenum, const std::string&);

    GLenum m_type {GL_COMPUTE_SHADER};
    GLuint m_id {0};
    std::string m_source {""};
    bool m_compiled {false};

};
}

#endif
