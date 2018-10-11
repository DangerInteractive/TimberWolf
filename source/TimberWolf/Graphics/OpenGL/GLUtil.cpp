#include "../../../../include/TimberWolf/Graphics/OpenGL/GLUtil.hpp"

GLenum tw::GLUtil::getType (GraphicsBufferable::DataType type) {

    switch (type) {

        case GraphicsBufferable::DataType::BYTE:
            return GL_BYTE;

        case GraphicsBufferable::DataType::UBYTE:
            return GL_UNSIGNED_BYTE;

        case GraphicsBufferable::DataType::SHORT:
            return GL_SHORT;

        case GraphicsBufferable::DataType::USHORT:
            return GL_UNSIGNED_SHORT;

        case GraphicsBufferable::DataType::INT:
            return GL_INT;

        case GraphicsBufferable::DataType::UINT:
            return GL_UNSIGNED_INT;

        case GraphicsBufferable::DataType::FLOAT:
            return GL_FLOAT;

        case GraphicsBufferable::DataType::DOUBLE:
            return GL_DOUBLE;

        default:
            return GL_FALSE; // this should probably break something

    }

}
