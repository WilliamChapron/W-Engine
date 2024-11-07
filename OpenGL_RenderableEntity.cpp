#include "pch.h"
#include "OpenGL_RenderableEntity.h"
#include "OpenGL_Shader.h"
#include "OpenGL_Mesh.h"
#include "SubMesh.h"
#include "OpenGL_SubMesh.h"
#include "RenderStructures.hpp"
#include "Primitive.h"

#include "Shader.h"
#include "Mesh.h"


OpenGL_RenderableEntity::OpenGL_RenderableEntity() {
    m_shader = nullptr;
    m_mesh = nullptr;
};

void OpenGL_RenderableEntity::Init() {
}

void OpenGL_RenderableEntity::SetShader(Shader* shader) {
    m_shader = static_cast<OpenGL_Shader*>(shader);
}

void OpenGL_RenderableEntity::SetMesh(Mesh* mesh) {
    m_mesh = static_cast<OpenGL_Mesh*>(mesh);
}

void OpenGL_RenderableEntity::Prepare() {
    m_shader->Use();
}