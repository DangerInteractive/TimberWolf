#include "../../../include/TimberWolf/Graphics/GraphicsBufferable.hpp"

size_t tw::GraphicsBufferable::getStoreBytes (unsigned int track) {

    return getDataTypeBytes() * getSegmentSize(track) * getSegmentCount();

}

size_t tw::GraphicsBufferable::getSegmentBytes (unsigned int track) {

    return getSegmentSize() * getDataTypeBytes();

}
