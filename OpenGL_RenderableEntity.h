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

    //void Prepare() override;

private:
    OpenGL_Shader* m_shader;
};

