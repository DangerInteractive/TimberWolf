#ifndef H_TW_GRAPHICSBUFFERABLE
#define H_TW_GRAPHICSBUFFERABLE

/**
 * @file
 *
 * Header file for the tw::GraphicsBufferable class.
 */

#include <cstddef>

namespace tw {
class GraphicsBufferable {

public:

    enum class DataType {
        BYTE, // 8-bit
        UBYTE,
        SHORT, // 16-bit
        USHORT,
        INT, // 32-bit
        UINT,
        FLOAT, // 32-bit IEEE-754
        DOUBLE // 64-bit IEEE-754
    };

    GraphicsBufferable () = default;
    virtual ~GraphicsBufferable () = default;

    GraphicsBufferable (GraphicsBufferable&&) = default;
    GraphicsBufferable& operator = (GraphicsBufferable&&) = default;

    GraphicsBufferable (const GraphicsBufferable&) = default;
    GraphicsBufferable& operator = (const GraphicsBufferable&) = default;

    // pure virtual methods, must be implemented by subclass
    virtual void* getDataPointer () = 0;
    virtual size_t getDataBytes () = 0;
    virtual unsigned int getSegmentCount () = 0;
    virtual int getSegmentSize (unsigned int = 0) = 0;
    virtual DataType getDataType (unsigned int = 0) = 0;
    virtual size_t getDataTypeBytes (unsigned int = 0) = 0;
    virtual bool isNormalized (unsigned int = 0) = 0;
    virtual size_t getStride (unsigned int = 0) = 0;
    virtual size_t getOffset (unsigned int = 0) = 0;

    // derivative of the pure virtuals, but can be overridden if needed
    virtual size_t getStoreBytes (unsigned int = 0);
    virtual size_t getSegmentBytes (unsigned int = 0);

};
}

#endif
