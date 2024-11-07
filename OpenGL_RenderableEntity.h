#pragma once

class OpenGL_Shader;
class OpenGL_Mesh;

#include "RenderableEntity.h"

class OpenGL_RenderableEntity : public RenderableEntity {
public:
    OpenGL_RenderableEntity();

    void Init() override;
    void Render(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& world) override;

    void SetShader(const std::string& vertexPath, const std::string& fragmentPath) override;
    void SetMesh(const std::string& filePath) override;

    inline OpenGL_Shader* GetShader() { return m_shader; }
    inline OpenGL_Mesh* GetMesh() { return m_mesh; }

    void Prepare() override;

private:
    OpenGL_Shader* m_shader;
    OpenGL_Mesh* m_mesh;
};

