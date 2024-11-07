#pragma once

class Primitive;
class Mesh;
class Shader;

class RenderableEntity
{
public:
    virtual ~RenderableEntity() = default;  

    virtual void SetMesh(Mesh* mesh) = 0;
    virtual void SetShader(Shader* shader) = 0;

    virtual void Init() = 0;
    virtual void Prepare() = 0;
};

