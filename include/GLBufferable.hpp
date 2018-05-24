#ifndef H_TW_GLBUFFERABLE
#define H_TW_GLBUFFERABLE

#include <GL/glew.h>

namespace tw {
class GLBufferable {

public:

    GLBufferable () = default;
    virtual ~GLBufferable () = default;

    GLBufferable (GLBufferable&&) = default;
    GLBufferable& operator = (GLBufferable&&) = default;

    GLBufferable (const GLBufferable&) = default;
    GLBufferable& operator = (const GLBufferable&) = default;

    // pure virtual methods, must be implemented by subclass
    virtual void* getDataPointer () = 0;
    virtual GLsizei getDataBytes () = 0;
    virtual GLuint getSegmentCount () = 0;
    virtual GLint getSegmentSize (unsigned int = 0) = 0;
    virtual constexpr GLenum getDataType (unsigned int = 0) = 0;
    virtual constexpr GLsizei getDataTypeBytes (unsigned int = 0) = 0;
    virtual GLboolean isNormalized (unsigned int = 0) = 0;
    virtual GLsizei getStride (unsigned int = 0) = 0;
    virtual GLsizei getOffset (unsigned int = 0) = 0;

    // derivative of the pure virtuals, but can be overridden if needed
    virtual GLsizei getStoreBytes (unsigned int = 0);
    virtual GLsizei getSegmentBytes (unsigned int = 0);

};
}

#endif
