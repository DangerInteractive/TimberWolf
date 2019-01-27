#ifndef TW_CLASS_GLUTIL
#define TW_CLASS_GLUTIL

#include <GL/glew.h>

#include "../GraphicsBufferable.hpp"

namespace tw {
class GLUtil {

public:

    static GLenum getType (GraphicsBufferable::DataType);

};
}

#endif
