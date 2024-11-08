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
    OpenGL_Mesh* mesh = static_cast<OpenGL_Mesh*>(glRE->GetMesh());
    OpenGL_Shader* shader = static_cast<OpenGL_Shader*>(glRE->GetShader());

    if (mesh && shader) {
        glRE->Prepare();
    }


    std::vector<SubMesh*> subMeshArray = mesh->GetSubMeshes();


    for (int i = 0; i < subMeshArray.size(); i++) {
        OpenGL_SubMesh* glSubMesh = static_cast<OpenGL_SubMesh*>(subMeshArray[i]); 

        // Prepare & draw Submesh
        OpenGL_Material* subMeshMaterial = static_cast<OpenGL_Material*>(mesh->GetMaterialByID(glSubMesh->GetMaterialID()));
        glSubMesh->Prepare(subMeshMaterial);

        // Link diffuse texture (0)
        if (subMeshMaterial) {
            GLint hasDiffuseLoc = glGetUniformLocation(shader->GetProgramID(), "hasDiffuseTexture");
            if (hasDiffuseLoc == -1) {
                std::cerr << "[ERROR] Uniform 'hasDiffuseTexture' not found in the shader!" << std::endl;
            }
            else {
                glUniform1i(hasDiffuseLoc, subMeshMaterial->m_hasDiffuseText);
            }
            if (subMeshMaterial->m_hasDiffuseText) {
                OpenGL_Texture* diffuseTexture = subMeshMaterial->GetDiffuseTexture();

                if (diffuseTexture) {
                    //std::cout << "[INFO] Diffuse Texture Found - ID: " << diffuseTexture->GetID() << std::endl;

                    // Liaison de la texture diffuse
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, diffuseTexture->GetID());
                    glUniform1i(glGetUniformLocation(shader->GetProgramID(), "u_DiffuseTexture"), 0);
                }
                else {
                    std::cout << "[WARNING] Diffuse Texture variable set but texture not found for Material ID: "
                        << glSubMesh->GetMaterialID() << std::endl;
                }
            }
            else {
                //std::cout << "[INFO] Material ID " << glSubMesh->GetMaterialID() << " has no diffuse texture, skipping binding." << std::endl;
            }
        }
        else {
            std::cout << "[WARNING] No Material found for SubMesh Index: " << i << std::endl;
        }




        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(glSubMesh->GetIndexCount()), GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
    }
    //std::cout << "[WARNING] No Material found for SubMesh Index: " << std::endl;

}



void OpenGL_Renderer::Present() {
    glfwSwapBuffers(m_context->getWindow());
    glfwPollEvents();
}

