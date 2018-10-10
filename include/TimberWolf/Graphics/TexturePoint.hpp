#ifndef TW_CLASS_TEXTUREPOINT
#define TW_CLASS_TEXTUREPOINT

/**
 * @file
 *
 * Header file for the tw::TexturePoint class.
 */

#include <algorithm>

namespace tw {
class TexturePoint {

public:

    TexturePoint () = default;
    TexturePoint (float, float);
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

    float m_u = 0.f;
    float m_v = 0.f;

};
}

#endif
