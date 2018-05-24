#ifndef H_TW_TEXTUREPOINT
#define H_TW_TEXTUREPOINT

#include <GL/glew.h>
#include <algorithm>

namespace tw {
class TexturePoint {

public:

    TexturePoint () = default;
    TexturePoint (GLfloat, GLfloat);
    ~TexturePoint () = default;

    TexturePoint (TexturePoint&&) = default;
    TexturePoint& operator = (TexturePoint&&) = default;

    TexturePoint (const TexturePoint&) = default;
    TexturePoint& operator = (const TexturePoint&) = default;

    float getU () const;
    float getV () const;

    void setU (float);
    void setV (float);

private:

    static float clamp (float);

    float m_u = 0.f;
    float m_v = 0.f;

};
}

#endif
