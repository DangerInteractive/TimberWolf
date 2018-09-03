#include "../../../include/TimberWolf/Graphics/Renderer.hpp"

void tw::Renderer::onWindowOpen () {

    return;

}

void tw::Renderer::onWindowClose () {

    return;

}

void tw::Renderer::render (const tw::Scene* scene) {

    for (auto puppet : scene->getPuppets()) {
        render(puppet.get());
    }

}

const tw::Color& tw::Renderer::getClearColor () const {

    return m_clearColor;

}

void tw::Renderer::setClearColor (const Color& color) {

    if (m_clearColor != color) {
        m_clearColor = color;
    }

}

void tw::Renderer::setClearColor (float r, float g, float b, float a) {

    auto color = Color(r, g, b, a);
    setClearColor(color);

}

void tw::Renderer::resetClearColor () {

    auto color = Color(0.f, 0.f, 0.f, 1.f);
    setClearColor(color);

}
