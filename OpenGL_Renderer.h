#pragma once

#include "Renderer.h"

class Context;
class OpenGL_Context;

class OpenGL_Renderer : public Renderer {
private:
    OpenGL_Context* m_context; 

public:
    OpenGL_Renderer() : m_context(nullptr) {}
    ~OpenGL_Renderer() {};

    void Initialize(Context* context) override;
    void Clear() override;                           
    void Draw(const Mesh& mesh, const Shader& shader) override;
    void Present() override;                          

};

