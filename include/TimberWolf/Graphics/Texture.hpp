#ifndef H_CLASS_TEXTURE
#define H_CLASS_TEXTURE

namespace tw {
class Texture {

public:

    Texture () = default;
    ~Texture () = default;

    Texture (Texture&&) = default;
    Texture& operator = (Texture&&) = default;

    Texture (const Texture&) = default;
    Texture& operator = (const Texture&) = default;

};
}

#endif
