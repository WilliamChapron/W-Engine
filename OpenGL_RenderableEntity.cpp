#include "pch.h"
#include "OpenGL_RenderableEntity.h"

#include "OpenGL_Shader.h"
#include "OpenGL_Mesh.h"

OpenGL_RenderableEntity::OpenGL_RenderableEntity() {};

void OpenGL_RenderableEntity::Init() {
    m_shader = new  OpenGL_Shader();
    m_mesh = new  OpenGL_Mesh();
}


void OpenGL_RenderableEntity::Render(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& world) {

};

void OpenGL_RenderableEntity::SetShader(const std::string& vertexPath, const std::string& fragmentPath) {
    if (!m_shader->Compile("res\\shaders\\vertex.glsl", "res\\shaders\\fragment.glsl")) {
        std::cerr << "Shader compilation failed!" << std::endl;
    }
}

void OpenGL_RenderableEntity::SetMesh(const std::string& filePath) {
    m_mesh->LoadFile(filePath);
}

void OpenGL_RenderableEntity::Prepare() {
    m_shader->Use();
}