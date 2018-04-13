#ifndef H_CLASS_RENDERER
#define H_CLASS_RENDERER

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Scene/Scene.hpp"

namespace tw {
class Renderer {

public:

    Renderer () = delete; // static only
    ~Renderer () = delete;

    Renderer (Renderer&&) = delete;
    Renderer& operator = (Renderer&&) = delete;

    Renderer (const Renderer&) = delete;
    Renderer& operator = (const Renderer&) = delete;

    void renderScene(Scene&);

};
}

#endif
