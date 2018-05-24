#include "../include/GLBufferable.hpp"

GLsizei tw::GLBufferable::getStoreBytes (unsigned int track) {

    return getDataTypeBytes() * getSegmentSize(track) * getSegmentCount();

}

GLsizei tw::GLBufferable::getSegmentBytes (unsigned int track) {

    return getSegmentSize() * getDataTypeBytes();

}
