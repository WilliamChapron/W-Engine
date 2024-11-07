#pragma once

class Texture;

class Material {
public:
    virtual ~Material() = default;

    virtual void Init(Texture* diffuseTexture) = 0;

    Texture* m_diffuseText;
    bool m_hasDiffuseText = false;
    Texture* m_mettalicText;
};