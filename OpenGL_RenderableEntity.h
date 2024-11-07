#pragma once

class OpenGL_Shader;
class OpenGL_Mesh;

class Mesh;
class Shader;

class Primitive;

#include "RenderableEntity.h"

class OpenGL_RenderableEntity : public RenderableEntity {
public:
    OpenGL_RenderableEntity();

    void Init() override;

    void SetShader(Shader* shader) override;
    void SetMesh(Mesh* mesh) override;
    
    inline OpenGL_Shader* GetShader() { return m_shader; }
    inline OpenGL_Mesh* GetMesh() { return m_mesh; }

    void Prepare() override;

private:
    OpenGL_Shader* m_shader;
    OpenGL_Mesh* m_mesh;
};

