#pragma once

class Texture;

class Material {
public:
    virtual ~Material() = default;

    virtual void Init(Texture* diffuseTexture) = 0;

    Texture* m_diffuseText;
    Texture* m_mettalicText;
};