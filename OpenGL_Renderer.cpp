#include "pch.h"


#include "OpenGL_Renderer.h"

#include "Context.h"  
#include "OpenGL_Context.h"  

#include "Shader.h"  
#include "OpenGL_Shader.h"  

#include "Mesh.h"  
#include "OpenGL_Mesh.h"  

#include "SubMesh.h"  
#include "OpenGL_SubMesh.h"  

#include "RenderableEntity.h"  
#include "OpenGL_RenderableEntity.h"  

#include "Material.h"  
#include "OpenGL_Material.h"  

void OpenGL_Renderer::Initialize(Context* context) {
    m_context = static_cast<OpenGL_Context*>(context);

    glEnable(GL_DEPTH_TEST);
}

void OpenGL_Renderer::Clear() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGL_Renderer::Draw(RenderableEntity* renderObject) {
    OpenGL_RenderableEntity* glRE = static_cast<OpenGL_RenderableEntity*>(renderObject);
    std::vector<SubMesh*> subMeshArray = glRE->GetSubMeshes();

    for (int i = 0; i < subMeshArray.size(); i++) {
        OpenGL_SubMesh* glSubMesh = static_cast<OpenGL_SubMesh*>(subMeshArray[i]);

        // Prepare & draw Submesh
        OpenGL_Material* subMeshMaterial = static_cast<OpenGL_Material*>(glRE->GetMaterialByID(glSubMesh->GetMaterialID()));
        OpenGL_Shader* shader = static_cast<OpenGL_Shader*>(subMeshMaterial->GetShader());

        if (shader) {
            shader->Use();
        }

        glSubMesh->Prepare(subMeshMaterial);

        // Lier la texture diffuse (0)
        if (subMeshMaterial) {
            GLint hasDiffuseLoc = glGetUniformLocation(shader->GetProgramID(), "hasDiffuseTexture");
            if (hasDiffuseLoc != -1) {
                glUniform1i(hasDiffuseLoc, subMeshMaterial->m_hasDiffuseText);
            }

            if (subMeshMaterial->m_hasDiffuseText) {
                OpenGL_Texture* diffuseTexture = subMeshMaterial->GetDiffuseTexture();

                if (diffuseTexture) {
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, diffuseTexture->GetID());
                    glUniform1i(glGetUniformLocation(shader->GetProgramID(), "u_DiffuseTexture"), 0);
                }
            }
        }

        // Assurez-vous de dessiner en mode triangles par défaut
        glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(glSubMesh->GetIndexCount()), GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
    }
}

void OpenGL_Renderer::DebugDraw(RenderableEntity* renderObject) {
    OpenGL_RenderableEntity* glRE = static_cast<OpenGL_RenderableEntity*>(renderObject);
    std::vector<SubMesh*> subMeshArray = glRE->GetSubMeshes();

    for (int i = 0; i < subMeshArray.size(); i++) {
        OpenGL_SubMesh* glSubMesh = static_cast<OpenGL_SubMesh*>(subMeshArray[i]);

        // Prepare & draw Submesh
        OpenGL_Material* subMeshMaterial = static_cast<OpenGL_Material*>(glRE->GetMaterialByID(glSubMesh->GetMaterialID()));
        OpenGL_Shader* shader = static_cast<OpenGL_Shader*>(subMeshMaterial->GetShader());

        if (shader) {
            shader->Use();
        }

        glSubMesh->Prepare(subMeshMaterial);


        glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);  
        glDrawElements(GL_LINE_STRIP, static_cast<GLsizei>(glSubMesh->GetIndexCount()), GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
    }
}


void OpenGL_Renderer::DebugColliderDraw(std::vector<float> lineVertices, std::vector<unsigned int> indices, OpenGL_Shader* shader) {
    shader->Use();

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind VBO et charger les données des sommets
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, lineVertices.size() * sizeof(float), lineVertices.data(), GL_STATIC_DRAW);

    // Bind EBO et charger les indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Configurer l'attribut de position des sommets (3 composantes par sommet)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Utiliser glPolygonMode pour afficher en mode lignes
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // Dessiner les polygones comme des lignes

    // Dessiner les polygones avec indices
    glDrawElements(GL_LINES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);

    // Réactiver le mode normal (mode plein)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // Retour au mode remplissage des polygones

    // Nettoyer
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
}

void OpenGL_Renderer::Present() {
    glfwSwapBuffers(m_context->getWindow());
    glfwPollEvents();
}

