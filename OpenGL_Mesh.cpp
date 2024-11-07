#include "pch.h"

#include "Texture.h"
#include "Material.h"

#include "OpenGL_Mesh.h"
#include "OpenGL_SubMesh.h"
#include "OpenGL_Texture.h"
#include "OpenGL_Material.h"





OpenGL_Mesh::OpenGL_Mesh() {}

OpenGL_Mesh::~OpenGL_Mesh() {
    for (auto subMesh : m_subMeshes) {
        delete subMesh;
    }
    for (auto texture : m_materials) {
        delete texture;
    }
}

//void OpenGL_Mesh::LoadFile(const std::string& filePath) {
//    m_scene = m_importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
//
//    if (!m_scene || m_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !m_scene->mRootNode) {
//        std::cerr << "Erreur : " << m_importer.GetErrorString() << std::endl;
//        return;
//    }
//
//    for (unsigned int i = 0; i < m_scene->mNumMeshes; i++) {
//        aiMesh* mesh = m_scene->mMeshes[i];
//
//        OpenGL_SubMesh* subMesh = new OpenGL_SubMesh();
//        subMesh->Setup(mesh);
//        AddSubMesh(subMesh);
//
//        aiMaterial* material = m_scene->mMaterials[mesh->mMaterialIndex];
//        aiString texturePath;
//
//        if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS) {
//            Texture* texture = new OpenGL_Texture(texturePath.C_Str());
//            Material* material = new OpenGL_Material();
//            material->Init(texture);
//
//            AddMaterial(material);
//            subMesh->SetMaterialID(static_cast<int>(m_materials.size() - 1));
//
//            std::cout << "SubMesh " << i << " linked to diffuse texture at path: " << texturePath.C_Str() << " with index: " << m_materials.size() - 1 << std::endl;
//        }
//        else {
//            std::cout << "SubMesh " << i << " has no diffuse texture." << std::endl;
//        }
//    }
//}

//void OpenGL_Mesh::AddSubMesh(SubMesh* subMesh) {
//    m_subMeshes.push_back(subMesh);
//}
//
//void OpenGL_Mesh::AddMaterial(Material* material) {
//    m_materials.push_back(material);
//}