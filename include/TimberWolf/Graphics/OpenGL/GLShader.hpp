#ifndef TW_CLASS_GLSHADER
#define TW_CLASS_GLSHADER

/**
 * @file
 *
 * Header file for the tw::GLShader class.
 */

#include <string>
#include <array>
#include <GL/glew.h>
#include "../../Log/Log.hpp"

namespace tw {
class GLShader {

public:

    GLShader () = delete; // parent class only
    virtual ~GLShader ();

    GLShader (GLShader&&) = default;
    GLShader& operator = (GLShader&&) = default;

    GLShader (const GLShader&) = delete; // not copyable
    GLShader& operator = (const GLShader&) = delete;

    GLenum getType () const;
    GLuint getId () const;
    std::string getSource () const;
    bool isCompiled () const;

    bool setSource (const std::string&);

    bool compile ();

protected:

    explicit GLShader (GLenum);
    GLShader (GLenum, const std::string&);

    GLenum m_type {GL_COMPUTE_SHADER};
    GLuint m_id {0};
    std::string m_source {""};
    bool m_compiled {false};

};
}

#endif
