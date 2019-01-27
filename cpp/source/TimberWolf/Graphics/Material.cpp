#include "../../../include/TimberWolf/Graphics/Material.hpp"

bool tw::Material::hasHandle () const {

    return m_handle != nullptr;

}

tw::MaterialHandle* tw::Material::getHandle () const {

    return m_handle.get();

}

void tw::Material::setHandle (std::unique_ptr<MaterialHandle>&& handle) {

    m_handle = std::move(handle);

}

void tw::Material::setHandle (MaterialHandle* handle) {

    setHandle(std::unique_ptr<MaterialHandle>(handle));

}

bool tw::Material::hasAmbience () const {

    return m_ambience != 0.f;

}

bool tw::Material::hasAmbientTexture () const {

    return m_ambientTextureOpacity > 0.f && m_ambientTexture != nullptr;

}

bool tw::Material::hasAmbienceMap () const {

    return m_ambienceMap != nullptr;

}

const tw::Color& tw::Material::getAmbientColor () const {

    return m_ambientColor;

}

float tw::Material::getAmbience () const {

    return m_ambience;

}

std::shared_ptr<tw::Texture> tw::Material::getAmbientTexture () const {

    return m_ambientTexture;

}

float tw::Material::getAmbientTextureOpacity () const {

    return m_ambientTextureOpacity;

}

std::shared_ptr<tw::Texture> tw::Material::getAmbienceMap () const {

    return m_ambienceMap;

}

bool tw::Material::hasSpecularity () const {

    return m_specularity != 0.f;

}

bool tw::Material::hasSpecularTexture () const {

    return m_specularTextureOpacity > 0.f && m_specularTexture != nullptr;

}

bool tw::Material::hasSpecularityMap () const {

    return m_specularityMap != nullptr;

}

bool tw::Material::hasSpecularDiffusionMap () const {

    return m_specularDiffusionMap != nullptr;

}

const tw::Color& tw::Material::getSpecularColor () const {

    return m_specularColor;

}

float tw::Material::getSpecularity () const {

    return m_specularity;

}

float tw::Material::getSpecularDiffusion () const {

    return m_specularDiffusion;

}

std::shared_ptr<tw::Texture> tw::Material::getSpecularTexture () const {

    return m_specularTexture;

}

float tw::Material::getSpecularTextureOpacity () const {

    return m_specularTextureOpacity;

}

std::shared_ptr<tw::Texture> tw::Material::getSpecularityMap () const {

    return m_specularityMap;

}

std::shared_ptr<tw::Texture> tw::Material::getSpecularDiffusionMap () const {

    return m_specularDiffusionMap;

}

bool tw::Material::hasDiffuse () const {

    return m_diffuse != 0.f;

}

bool tw::Material::hasDiffuseTexture () const {

    return m_diffuseTextureOpacity > 0.f && m_diffuseTexture != nullptr;

}

bool tw::Material::hasDiffuseMap () const {

    return m_diffuseMap != nullptr;

}

bool tw::Material::hasDiffuseDiffusionMap () const {

    return m_diffuseDiffusionMap != nullptr;

}

const tw::Color& tw::Material::getDiffuseColor () const {

    return m_diffuseColor;

}

float tw::Material::getDiffuse () const {

    return m_diffuse;

}

float tw::Material::getDiffuseDiffusion () const {

    return m_diffuseDiffusion;

}

std::shared_ptr<tw::Texture> tw::Material::getDiffuseTexture () const {

    return m_diffuseTexture;

}

float tw::Material::getDiffuseTextureOpacity () const {

    return m_diffuseTextureOpacity;

}

std::shared_ptr<tw::Texture> tw::Material::getDiffuseMap () const {

    return m_diffuseMap;

}

std::shared_ptr<tw::Texture> tw::Material::getDiffuseDiffusionMap () const {

    return m_diffuseDiffusionMap;

}

bool tw::Material::hasNormalMap () const {

    return m_normalMap != nullptr;

}

bool tw::Material::hasBumpMap () const {

    return m_bumpMap != nullptr;

}

bool tw::Material::hasDisplacementMap () const {

    return m_displacementMap != nullptr;

}

bool tw::Material::hasParallaxMap () const {

    return m_parallaxMap != nullptr;

}

std::shared_ptr<tw::Texture> tw::Material::getNormalMap () const {

    return m_normalMap;

}

std::shared_ptr<tw::Texture> tw::Material::getBumpMap () const {

    return m_bumpMap;

}

std::shared_ptr<tw::Texture> tw::Material::getDisplacementMap () const {

    return m_displacementMap;

}

std::shared_ptr<tw::Texture> tw::Material::getParallaxMap () const {

    return m_parallaxMap;

}

bool tw::Material::transparencyEnabled () const {

    return m_transparencyEnabled;

}

tw::Material& tw::Material::setAmbientColor (const Color& color) {

    m_ambientColor = color;
    return *this;

}

tw::Material& tw::Material::setAmbience (float ambience) {

    m_ambience = ambience;
    return *this;

}

tw::Material& tw::Material::setAmbientTexture (const std::shared_ptr<Texture>& texture) {

    m_ambientTexture = texture;
    return *this;

}

tw::Material& tw::Material::setAmbientTextureOpacity (float opacity) {

    m_ambientTextureOpacity = std::clamp(opacity, 0.f, 1.f);
    return *this;

}

tw::Material& tw::Material::setAmbienceMap (const std::shared_ptr<Texture>& texture) {

    m_ambienceMap = texture;
    return *this;

}

tw::Material& tw::Material::setSpecularColor (const Color& color) {

    m_specularColor = color;
    return *this;

}

tw::Material& tw::Material::setSpecularity (float specularity) {

    m_specularity = std::clamp(specularity, 0.f, INFINITY);
    return *this;

}

tw::Material& tw::Material::setSpecularDiffusion (float diffusion) {

    m_specularDiffusion = std::clamp(diffusion, 0.f, 1.f);
    return *this;

}

tw::Material& tw::Material::setSpecularTexture (const std::shared_ptr<Texture>& texture) {

    m_specularTexture = texture;
    return *this;

}

tw::Material& tw::Material::setSpecularTextureOpacity (float opacity) {

    m_specularTextureOpacity = std::clamp(opacity, 0.f, 1.f);
    return *this;

}

tw::Material& tw::Material::setSpecularityMap (const std::shared_ptr<Texture>& texture) {

    m_specularityMap = texture;
    return *this;

}

tw::Material& tw::Material::setSpecularDiffusionMap (const std::shared_ptr<Texture>& texture) {

    m_specularDiffusionMap = texture;
    return *this;

}

tw::Material& tw::Material::setDiffuseColor (const Color& color) {

    m_diffuseColor = color;
    return *this;

}

tw::Material& tw::Material::setDiffuse (float diffuse) {

    m_diffuse = std::clamp(diffuse, 0.f, INFINITY);
    return *this;

}

tw::Material& tw::Material::setDiffuseDiffusion (float diffusion) {

    m_diffuseDiffusion = std::clamp(diffusion, 0.f, 1.f);
    return *this;

}

tw::Material& tw::Material::setDiffuseTexture (const std::shared_ptr<Texture>& texture) {

    m_diffuseTexture = texture;
    return *this;

}

tw::Material& tw::Material::setDiffuseTextureOpacity (float opacity) {

    m_diffuseTextureOpacity = std::clamp(opacity, 0.f, 1.f);
    return *this;

}

tw::Material& tw::Material::setDiffuseMap (const std::shared_ptr<Texture>& texture) {

    m_diffuseMap = texture;
    return *this;

}

tw::Material& tw::Material::setDiffuseDiffusionMap (const std::shared_ptr<Texture>& texture) {

    m_diffuseDiffusionMap = texture;
    return *this;

}

tw::Material& tw::Material::setNormalMap (const std::shared_ptr<Texture>& texture) {

    m_normalMap = texture;
    return *this;

}

tw::Material& tw::Material::setBumpMap (const std::shared_ptr<Texture>& texture) {

    m_bumpMap = texture;
    return *this;

}

tw::Material& tw::Material::setDisplacementMap (const std::shared_ptr<Texture>& texture) {

    m_displacementMap = texture;
    return *this;

}

tw::Material& tw::Material::setParallaxMap (const std::shared_ptr<Texture>& texture) {

    m_parallaxMap = texture;
    return *this;

}

tw::Material& tw::Material::enableTransparency () {

    m_transparencyEnabled = true;
    return *this;

}

tw::Material& tw::Material::disableTransparency () {

    m_transparencyEnabled = false;
    return *this;

}
