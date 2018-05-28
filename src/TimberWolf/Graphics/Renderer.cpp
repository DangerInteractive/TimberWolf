#include "../../../include/TimberWolf/Graphics/Renderer.hpp"

void tw::Renderer::clear (const Color& color) {

    clearColor(color);
    clearDepth();

}

void tw::Renderer::clear () {

    clearColor();
    clearDepth();

}

void tw::Renderer::onWindowOpen () {

    return;

}

void tw::Renderer::onWindowClose () {

    return;

}

tw::Color tw::Renderer::getDefaultClearColor () {

    return Color(0.f, 0.f, 0.f, 1.f);

}
