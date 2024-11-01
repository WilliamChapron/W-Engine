#pragma once

#include "Shader.h" 
#include "Mesh.h" 

class Context;


class Renderer {
public:
    virtual ~Renderer() = default;

    virtual void Initialize(Context* context) = 0;
    virtual void Clear() = 0;
    virtual void Draw(const Mesh& mesh, const Shader& shader) = 0;
    virtual void Present() = 0;
};
