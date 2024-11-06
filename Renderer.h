#pragma once

#include "Shader.h" 
#include "Mesh.h" 

class Context;

#include "RenderableEntity.h" 

class Renderer {
public:
    virtual ~Renderer() = default;

    virtual void Initialize(Context* context) = 0;
    virtual void Clear() = 0;
    virtual void Draw(RenderableEntity* renderObject) = 0;
    virtual void Present() = 0;
};
