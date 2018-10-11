#include "../../../include/TimberWolf/Graphics/GraphicsBufferable.hpp"

size_t tw::GraphicsBufferable::getStoreBytes (uint8_t track) const {

    return getDataTypeBytes() * getSegmentSize(track) * getSegmentCount();

}

size_t tw::GraphicsBufferable::getSegmentBytes (uint8_t track) const {

    return getSegmentSize() * getDataTypeBytes();

}
