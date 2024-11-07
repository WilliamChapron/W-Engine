#pragma once

class Primitive;

class RenderableEntity
{
public:
    virtual ~RenderableEntity() = default;  
    virtual void Render(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& world) = 0;

    virtual void SetShader(const std::string& vertexPath, const std::string& fragmentPath) = 0;

    virtual void SetMesh(const std::string& filePath) = 0;
    virtual void SetMesh(const Primitive* primitive) = 0;

    virtual void Init() = 0;
    virtual void Prepare() = 0;
};

