#include "../../../include/TimberWolf/Graphics/GraphicsBufferable.hpp"

size_t tw::GraphicsBufferable::getStoreBytes (uint8_t track) {

    return getDataTypeBytes() * getSegmentSize(track) * getSegmentCount();

}

size_t tw::GraphicsBufferable::getSegmentBytes (uint8_t track) {

    return getSegmentSize() * getDataTypeBytes();

}
