#pragma once

#include "Material.h"
#include "Texture.h"

#include "OpenGL_Texture.h"

#include "OpenGL_Shader.h"

class OpenGL_Material : public Material {
public:
    OpenGL_Material() {};
    ~OpenGL_Material() override {};

    inline void SetDiffuseTexture(Texture* diffuseTexture) override {m_diffuseText = diffuseTexture;}
    inline void SetShader(Shader* shader) override { m_shader = shader;}

    inline OpenGL_Shader* GetShader() { return static_cast<OpenGL_Shader*>(m_shader); };
    inline OpenGL_Texture* GetDiffuseTexture() { return static_cast<OpenGL_Texture*>(m_diffuseText); };


    glm::vec3 m_diffuse;
    float m_metallic;
    float m_roughness;
    glm::vec3 m_specular;
};