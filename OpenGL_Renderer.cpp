#include "pch.h"


#include "OpenGL_Renderer.h"

#include "Context.h"  
#include "OpenGL_Context.h"  

#include "Shader.h"  
#include "OpenGL_Shader.h"  

#include "Mesh.h"  
#include "OpenGL_Mesh.h"  

#include "Submesh.h"  
#include "OpenGL_Submesh.h"  

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
    std::vector<Submesh*> subMeshArray = glRE->GetSubMeshes();

    for (int i = 0; i < subMeshArray.size(); i++) {
        OpenGL_Submesh* glSubMesh = static_cast<OpenGL_Submesh*>(subMeshArray[i]);

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

void OpenGL_Renderer::WireFrameDraw(RenderableEntity* renderObject) {
    OpenGL_RenderableEntity* glRE = static_cast<OpenGL_RenderableEntity*>(renderObject);
    std::vector<Submesh*> subMeshArray = glRE->GetSubMeshes();

    for (int i = 0; i < subMeshArray.size(); i++) {
        OpenGL_Submesh* glSubMesh = static_cast<OpenGL_Submesh*>(subMeshArray[i]);

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


void OpenGL_Renderer::DrawBoundingBoxCorners(std::vector<float> lineVertices, std::vector<unsigned int> indices, OpenGL_Shader* shader) {
    shader->Use();

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind VAO
    glBindVertexArray(VAO);

    std::vector<float> colors = {
       1.0f, 0.0f, 0.0f, 1.0f, // Corner 0 → Red
       0.0f, 1.0f, 0.0f, 1.0f, // Corner 1 → Green
       0.0f, 0.0f, 1.0f, 1.0f, // Corner 2 → Blue
       1.0f, 1.0f, 0.0f, 1.0f, // Corner 3 → Yellow
       1.0f, 0.0f, 1.0f, 1.0f, // Corner 4 → Magenta
       0.0f, 1.0f, 1.0f, 1.0f, // Corner 5 → Cyan
       1.0f, 0.5f, 0.0f, 1.0f, // Corner 6 → Orange
       0.5f, 0.0f, 0.5f, 1.0f  // Corner 7 → Purple
    };

    // Combine positions and colors into one array
    std::vector<float> verticesWithColor;
    for (size_t i = 0; i < lineVertices.size() / 3; ++i) {
        verticesWithColor.push_back(lineVertices[i * 3]);
        verticesWithColor.push_back(lineVertices[i * 3 + 1]);
        verticesWithColor.push_back(lineVertices[i * 3 + 2]);

        verticesWithColor.push_back(colors[i * 4]);
        verticesWithColor.push_back(colors[i * 4 + 1]);
        verticesWithColor.push_back(colors[i * 4 + 2]);
        verticesWithColor.push_back(colors[i * 4 + 3]);
    }

    // Bind VBO and load vertex data (with colors)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesWithColor.size() * sizeof(float), verticesWithColor.data(), GL_STATIC_DRAW);

    // Bind EBO and load indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Set up vertex position attribute (3 components per vertex)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0); // 7 = 3 position + 4 color
    glEnableVertexAttribArray(0);

    // Set up color attribute (4 components per vertex)
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float))); // Color starts at index 3
    glEnableVertexAttribArray(1);

    // Use glPolygonMode to draw in line mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // Draw polygons as lines

    // Draw bounding box lines
    glDrawElements(GL_LINES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);

    // Switch back to normal fill mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // Back to polygon fill mode

    // Set up for drawing points
    glPointSize(8.0f); // Point size (adjust as needed)
    glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(lineVertices.size() / 3)); // Draw each vertex as a point

    // Cleanup
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
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

