#include "pch.h"


#include "OpenGL_Renderer.h"

#include "Context.h"  
#include "OpenGL_Context.h"  

#include "Shader.h"  

#include "Mesh.h"  
#include "OpenGL_Mesh.h"  

void OpenGL_Renderer::Initialize(Context* context) {
    m_context = static_cast<OpenGL_Context*>(context);
}

void OpenGL_Renderer::Clear() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGL_Renderer::Draw(const Mesh& mesh, const Shader& shader) {

    const OpenGL_Mesh& glMesh = static_cast<const OpenGL_Mesh&>(mesh);

    // Liaison du VAO du mesh
    glBindVertexArray(glMesh.GetVAO()); 

    // Dessinez
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(glMesh.GetIndexCount()), GL_UNSIGNED_INT, 0); // Dessine avec des indices

    // D�liez le VAO (facultatif, mais souvent une bonne pratique)
    glBindVertexArray(0);
}

void OpenGL_Renderer::Present() {
    glfwSwapBuffers(m_context->getWindow());
    glfwPollEvents();
}
