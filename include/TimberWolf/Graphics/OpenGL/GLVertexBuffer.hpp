#ifndef TW_CLASS_GLVERTEXBUFFER
#define TW_CLASS_GLVERTEXBUFFER

/**
 * @file
 *
 * Header file for the tw::GLVertexBuffer class.
 */

#include <cstdint>
#include <GL/glew.h>

#include "../GraphicsBufferable.hpp"

namespace tw {
class GLVertexBuffer {

public:

    GLVertexBuffer ();
    explicit GLVertexBuffer (GLuint);
    ~GLVertexBuffer ();

    GLVertexBuffer (GLVertexBuffer&&) = default;
    GLVertexBuffer& operator = (GLVertexBuffer&&) = default;

    GLVertexBuffer (const GLVertexBuffer&) = delete; // not copyable
    GLVertexBuffer& operator = (const GLVertexBuffer&) = delete;

    GLuint getId () const;

    uint32_t getSegmentSize () const;
    GraphicsBufferable::DataType getDataType () const;
    bool isNormalized () const;

    void bind ();
    static void unbind ();

    void buffer (GraphicsBufferable*, uint8_t);

private:

    GLuint m_id {0};

    uint32_t m_segmentSize {0};
    GraphicsBufferable::DataType m_type {GraphicsBufferable::DataType::FLOAT};
    bool m_normalized {false};

};
}

#endif
