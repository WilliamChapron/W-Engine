#include "pch.h"

#include "Texture.h"

#include "OpenGL_Mesh.h"
#include "OpenGL_SubMesh.h"
#include "OpenGL_Texture.h"





OpenGL_Mesh::OpenGL_Mesh() {}

OpenGL_Mesh::~OpenGL_Mesh() {
    for (auto subMesh : m_subMeshes) {
        delete subMesh;
    }
    for (auto texture : m_diffuseTextures) {
        delete texture;
    }
}

void OpenGL_Mesh::LoadPrimitive() {
    
}

void OpenGL_Mesh::LoadFile(const std::string& filePath) {
    m_scene = m_importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    if (!m_scene || m_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !m_scene->mRootNode) {
        std::cerr << "Erreur : " << m_importer.GetErrorString() << std::endl;
        return;
    }

    for (unsigned int i = 0; i < m_scene->mNumMeshes; i++) {
        aiMesh* mesh = m_scene->mMeshes[i];

        OpenGL_SubMesh* subMesh = new OpenGL_SubMesh();
        subMesh->Setup(mesh);
        AddSubMesh(subMesh);

        aiMaterial* material = m_scene->mMaterials[mesh->mMaterialIndex];
        aiString texturePath;

        if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS) {
            //Texture* texture = new OpenGL_Texture(std::string(texturePath.C_Str()));

            //AddDiffuseTexture(texture);
            subMesh->SetTextureInfo(m_diffuseTextures.size());
        }
    }
}

void OpenGL_Mesh::AddSubMesh(SubMesh* subMesh) {
    m_subMeshes.push_back(subMesh);
}

void OpenGL_Mesh::AddDiffuseTexture(Texture* texture) {
    m_diffuseTextures.push_back(texture);
}