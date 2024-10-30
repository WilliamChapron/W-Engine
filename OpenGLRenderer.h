#pragma once

#include "Renderer.h"
#include "OpenGLContext.h"  

class OpenGL_Renderer : public Renderer {
private:
    OpenGLContext* m_context; 

public:
    OpenGL_Renderer() {};
    virtual ~OpenGL_Renderer() {};

    void Initialize(Context* context) override;
    void Clear() override;                           
    void Draw(const std::vector<float>& vertices, const Shader& shader) override;
    void Present() override;                          

};

