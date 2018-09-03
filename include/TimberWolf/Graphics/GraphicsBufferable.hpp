#ifndef TW_CLASS_GRAPHICSBUFFERABLE
#define TW_CLASS_GRAPHICSBUFFERABLE

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

    enum ToBuffer {
        ATTRIB_0 = 1 << 0,
        ATTRIB_1 = 1 << 1,
        ATTRIB_2 = 1 << 2,
        ATTRIB_3 = 1 << 3,
        ATTRIB_4 = 1 << 4,
        ATTRIB_5 = 1 << 5,
        ATTRIB_6 = 1 << 6,
        ATTRIB_7 = 1 << 7,
        ATTRIB_8 = 1 << 8,
        ATTRIB_9 = 1 << 9,
        ATTRIB_10 = 1 << 10,
        ATTRIB_11 = 1 << 11,
        ATTRIB_12 = 1 << 12,
        ATTRIB_13 = 1 << 13,
        ATTRIB_14 = 1 << 14,
        ATTRIB_15 = 1 << 15,
        ATTRIB_ALL = 0x0000FFFF
    };

    GraphicsBufferable () = default;
    virtual ~GraphicsBufferable () = default;

    GraphicsBufferable (GraphicsBufferable&&) = default;
    GraphicsBufferable& operator = (GraphicsBufferable&&) = default;

    GraphicsBufferable (const GraphicsBufferable&) = default;
    GraphicsBufferable& operator = (const GraphicsBufferable&) = default;

    // pure virtual methods, must be implemented by subclass
    virtual unsigned int getTracksToBuffer () = 0;
    virtual void* getDataPointer (unsigned int = 0) = 0;
    virtual size_t getDataBytes (unsigned int = 0) = 0;
    virtual unsigned int getSegmentCount (unsigned int = 0) = 0;
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
