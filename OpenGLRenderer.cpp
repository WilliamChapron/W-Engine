#include "pch.h"

#include "OpenGLRenderer.h"

#include "Context.h"  
#include "OpenGLContext.h"  

#include "Shader.h"  

void OpenGL_Renderer::Initialize(Context* context) {
    m_context = static_cast<OpenGLContext*>(context);
}

void OpenGL_Renderer::Clear() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGL_Renderer::Draw(const std::vector<float>& vertices, const Shader& shader) {
    shader.Use();

    // Configuration des vertex buffers
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Configurer les attributs de vertex ici
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Dessinez
    glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3); // suppose qu'il s'agit d'un ensemble de triangles

    // Nettoyage
    glDeleteBuffers(1, &VBO);
}

void OpenGL_Renderer::Present() {
    glfwSwapBuffers(m_context->getWindow());
    glfwPollEvents();
}

