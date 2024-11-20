#include "pch.h"
#include "GLFWLoader.h"

#include "Texture.h"
#include "Material.h"

#include "OpenGL_Mesh.h"
#include "OpenGL_SubMesh.h"
#include "OpenGL_Texture.h"
#include "OpenGL_Material.h"

#include "ResourceManager.hpp"

void GLFWLoader::LoadFile(const std::string& filePath) {
    m_scene = m_importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    if (!m_scene || m_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !m_scene->mRootNode) {
        std::cerr << "Erreur : " << m_importer.GetErrorString() << std::endl;
        return;
    }

    for (unsigned int i = 0; i < m_scene->mNumMeshes; i++) {
        aiMesh* mesh = m_scene->mMeshes[i];

        OpenGL_SubMesh* subMesh = new OpenGL_SubMesh();
        LoadAiMesh(mesh, subMesh);  
        subMesh->SetupBinding();
        m_subMeshes.push_back(subMesh);  

        aiMaterial* material = m_scene->mMaterials[mesh->mMaterialIndex];
        aiString texturePath;

        if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS) {
            OpenGL_ResourceManager& instance = OpenGL_ResourceManager::GetInstance();

            // Get texture path from file path ex :  res/models/dodge/textures/
            std::string fTextPath = filePath.c_str();
            size_t lastSlashPos = fTextPath.find_last_of("/");
            if (lastSlashPos != std::string::npos) { fTextPath.erase(lastSlashPos + 1);}
            fTextPath += texturePath.C_Str();
            //

            Texture* texture = new OpenGL_Texture(fTextPath.c_str());
            OpenGL_Texture* glTexture = static_cast<OpenGL_Texture*>(texture);
            int textureID = instance.AddTexture(glTexture) + 1;
            OpenGL_Material* material = new OpenGL_Material();
            material->m_hasDiffuseText = true;
            material->SetDiffuseTexture(texture);

            m_materials.push_back(material);  

            subMesh->SetMaterialID(static_cast<int>(m_materials.size() - 1));  
        }
        else {
            OpenGL_Material* material = new OpenGL_Material();
            m_materials.push_back(material);
            subMesh->SetMaterialID(static_cast<int>(m_materials.size() - 1));
            std::cout << "SubMesh " << i << " has no diffuse texture." << std::endl;
        }
    }
}

void GLFWLoader::LoadAiMesh(aiMesh* mesh, SubMesh* subMesh) {
    for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
        Vertex vertex;
        vertex.position[0] = mesh->mVertices[j].x;
        vertex.position[1] = mesh->mVertices[j].y;
        vertex.position[2] = mesh->mVertices[j].z;

        if (mesh->mNormals) {
            vertex.normal[0] = mesh->mNormals[j].x;
            vertex.normal[1] = mesh->mNormals[j].y;
            vertex.normal[2] = mesh->mNormals[j].z;
        }

        if (mesh->mTextureCoords[0]) {
            vertex.texCoords[0] = mesh->mTextureCoords[0][j].x;
            vertex.texCoords[1] = mesh->mTextureCoords[0][j].y;
        }
        else {
            vertex.texCoords[0] = 0.0f;
            vertex.texCoords[1] = 0.0f;
        }

        subMesh->m_vertices.push_back(vertex); 
    }

    for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
        aiFace face = mesh->mFaces[j];
        for (unsigned int k = 0; k < face.mNumIndices; k++) {
            subMesh->m_indices.push_back(face.mIndices[k]);  
        }
    }
}

// All Mesh

void GLFWLoader::StoreSceneAllVertices() {
    for (unsigned int i = 0; i < m_scene->mNumMeshes; i++) {
        aiMesh* mesh = m_scene->mMeshes[i];

        for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
            aiVector3D vertex = mesh->mVertices[j];

            float* vertexArray = new float[3];
            vertexArray[0] = vertex.x;
            vertexArray[1] = vertex.y;
            vertexArray[2] = vertex.z;

            m_allVertices.push_back(vertexArray);
            
            // FindMinMaxFromVerticesPack
            m_min[0] = std::min(m_min[0], vertex[0]);
            m_min[1] = std::min(m_min[1], vertex[1]);
            m_min[2] = std::min(m_min[2], vertex[2]);

            m_max[0] = std::max(m_max[0], vertex[0]);
            m_max[1] = std::max(m_max[1], vertex[1]);
            m_max[2] = std::max(m_max[2], vertex[2]);
        }
    }

    //std::cout << "Total number of vertices: " << m_allVertices.size() << std::endl;
}