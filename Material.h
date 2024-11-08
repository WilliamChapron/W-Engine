#pragma once

class Texture;
class Shader;

class Material {
public:
    virtual ~Material() = default;


    virtual void SetShader(Shader* shader) = 0;
    virtual void SetDiffuseTexture(Texture* diffuseTexture) = 0;

    Shader* m_shader = nullptr;

    Texture* m_diffuseText;
    bool m_hasDiffuseText = false;
    Texture* m_mettalicText;
};