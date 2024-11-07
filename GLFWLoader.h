#pragma once

class Material;
class SubMesh;

class GLFWLoader {
public:
    GLFWLoader() = default;

    void LoadFile(const std::string& filePath);

    std::vector<SubMesh*> m_subMeshes;
    std::vector<Material*> m_materials;
private:
    void LoadAiMesh(aiMesh* mesh, SubMesh* subMesh);

    Assimp::Importer m_importer;
    const aiScene* m_scene;
};