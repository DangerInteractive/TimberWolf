#ifndef TW_CLASS_MATERIAL
#define TW_CLASS_MATERIAL

#include <memory>
#include "../Core/Color.hpp"
#include "Texture.hpp"

namespace tw {
class Material {

public:

    Material () = default;
    ~Material () = default;

    Material (Material&&) = default;
    Material& operator = (Material&&) = default;

    Material (const Material&) = default;
    Material& operator = (const Material&) = default;

    bool hasAmbience () const;
    bool hasAmbientTexture () const;
    bool hasAmbienceMap () const;
    const Color& getAmbientColor () const;
    float getAmbience () const;
    std::shared_ptr<Texture> getAmbientTexture () const;
    float getAmbientTextureOpacity () const;
    std::shared_ptr<Texture> getAmbienceMap () const;

    bool hasSpecularity () const;
    bool hasSpecularTexture () const;
    bool hasSpecularityMap () const;
    bool hasSpecularDiffusionMap () const;
    const Color& getSpecularColor () const;
    float getSpecularity () const;
    float getSpecularDiffusion () const;
    std::shared_ptr<Texture> getSpecularTexture () const;
    float getSpecularTextureOpacity () const;
    std::shared_ptr<Texture> getSpecularityMap () const;
    std::shared_ptr<Texture> getSpecularDiffusionMap () const;

    bool hasDiffuse () const;
    bool hasDiffuseTexture () const;
    bool hasDiffuseMap () const;
    bool hasDiffuseDiffusionMap () const;
    const Color& getDiffuseColor () const;
    float getDiffuse () const;
    float getDiffuseDiffusion () const;
    std::shared_ptr<Texture> getDiffuseTexture () const;
    float getDiffuseTextureOpacity () const;
    std::shared_ptr<Texture> getDiffuseMap () const;
    std::shared_ptr<Texture> getDiffuseDiffusionMap () const;

    bool hasNormalMap () const;
    bool hasBumpMap () const;
    bool hasDisplacementMap () const;
    bool hasParallaxMap () const;
    std::shared_ptr<Texture> getNormalMap () const;
    std::shared_ptr<Texture> getBumpMap () const;
    std::shared_ptr<Texture> getDisplacementMap () const;
    std::shared_ptr<Texture> getParallaxMap () const;

    bool transparencyEnabled () const;

    Material& setAmbientColor (const Color&);
    Material& setAmbience (float);
    Material& setAmbientTexture (const std::shared_ptr<Texture>&);
    Material& setAmbientTextureOpacity (float);
    Material& setAmbienceMap (const std::shared_ptr<Texture>&);

    Material& setSpecularColor (const Color&);
    Material& setSpecularity (float);
    Material& setSpecularDiffusion (float);
    Material& setSpecularTexture (const std::shared_ptr<Texture>&);
    Material& setSpecularTextureOpacity (float);
    Material& setSpecularityMap (const std::shared_ptr<Texture>&);
    Material& setSpecularDiffusionMap (const std::shared_ptr<Texture>&);

    Material& setDiffuseColor (const Color&);
    Material& setDiffuse (float);
    Material& setDiffuseDiffusion (float);
    Material& setDiffuseTexture (const std::shared_ptr<Texture>&);
    Material& setDiffuseTextureOpacity (float);
    Material& setDiffuseMap (const std::shared_ptr<Texture>&);
    Material& setDiffuseDiffusionMap (const std::shared_ptr<Texture>&);

    Material& setNormalMap (const std::shared_ptr<Texture>&);
    Material& setBumpMap (const std::shared_ptr<Texture>&);
    Material& setDisplacementMap (const std::shared_ptr<Texture>&);
    Material& setParallaxMap (const std::shared_ptr<Texture>&);

    Material& enableTransparency ();
    Material& disableTransparency ();

private:

    // ambient illumination
    Color m_ambientColor {};
    float m_ambience {0.f};
    std::shared_ptr<Texture> m_ambientTexture {nullptr};
    float m_ambientTextureOpacity {0.f};
    std::shared_ptr<Texture> m_ambienceMap {nullptr};

    // specular reflection
    Color m_specularColor {};
    float m_specularity {0.f};
    float m_specularDiffusion {0.1f};
    std::shared_ptr<Texture> m_specularTexture {nullptr};
    float m_specularTextureOpacity {0.f};
    std::shared_ptr<Texture> m_specularityMap {nullptr};
    std::shared_ptr<Texture> m_specularDiffusionMap {nullptr};

    // diffuse reflection
    Color m_diffuseColor {};
    float m_diffuse {0.f};
    float m_diffuseDiffusion {1.f};
    std::shared_ptr<Texture> m_diffuseTexture {nullptr};
    float m_diffuseTextureOpacity {0.f};
    std::shared_ptr<Texture> m_diffuseMap {nullptr};
    std::shared_ptr<Texture> m_diffuseDiffusionMap {nullptr};

    // pseudo-texturing
    std::shared_ptr<Texture> m_normalMap {nullptr};
    std::shared_ptr<Texture> m_bumpMap {nullptr};
    std::shared_ptr<Texture> m_displacementMap {nullptr};
    std::shared_ptr<Texture> m_parallaxMap {nullptr};

    // material transparency rendering
    bool m_transparencyEnabled {false};

};
}

#endif
