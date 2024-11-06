#include "pch.h"


#include "OpenGL_Renderer.h"

#include "Context.h"  
#include "OpenGL_Context.h"  

#include "Shader.h"  

#include "Mesh.h"  
#include "OpenGL_Mesh.h"  

#include "OpenGL_SubMesh.h"  

#include "RenderableEntity.h"  
#include "OpenGL_RenderableEntity.h"  

void OpenGL_Renderer::Initialize(Context* context) {
    m_context = static_cast<OpenGL_Context*>(context);
}

void OpenGL_Renderer::Clear() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGL_Renderer::Draw(RenderableEntity* renderObject) {

    OpenGL_RenderableEntity* glRE = static_cast<OpenGL_RenderableEntity*>(renderObject);
    OpenGL_Mesh* mesh = static_cast<OpenGL_Mesh*>(glRE->GetMesh());
    OpenGL_Shader* shader = static_cast<OpenGL_Shader*>(glRE->GetShader());

    if (mesh && shader) {
        //glRE->Prepare();
    }


    for (auto& subMesh : mesh->GetSubMeshes()) {
        OpenGL_SubMesh* openGLSubMesh = static_cast<OpenGL_SubMesh*>(subMesh); // Convertir SubMesh en OpenGL_SubMesh

        //// Préparer le SubMesh
        //openGLSubMesh->Update();  // Mise à jour des données du SubMesh si nécessaire
        //openGLSubMesh->Prepare(); // S'assurer que le SubMesh est prêt à être dessiné

        //// Lier la texture associée à ce SubMesh (s'il y en a une)
        //if (openGLSubMesh->m_aText >= 0) {  // Si une texture est associée
        //    glActiveTexture(GL_TEXTURE0);
        //    glBindTexture(GL_TEXTURE_2D, openGLSubMesh->m_diffuseTextures[openGLSubMesh->m_aText]->GetID());
        //}

        //// Lier le VAO du SubMesh pour le rendu
        //glBindVertexArray(openGLSubMesh->GetVAO());

        //// Dessiner les éléments de ce SubMesh
        //glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(openGLSubMesh->GetIndexCount()), GL_UNSIGNED_INT, 0);

        //// Libérer le VAO pour ce SubMesh
        //glBindVertexArray(0);
    }

    //glBindVertexArray(mesh->GetVAO());

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
    //glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(glMesh.GetIndexCount()), GL_UNSIGNED_INT, 0); 

    //glBindVertexArray(0);
}

void OpenGL_Renderer::Present() {
    glfwSwapBuffers(m_context->getWindow());
    glfwPollEvents();
}

