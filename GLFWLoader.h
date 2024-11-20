#pragma once

class Material;
class SubMesh;

class GLFWLoader {
public:
    GLFWLoader() = default;

    void LoadFile(const std::string& filePath);

    std::vector<SubMesh*> m_subMeshes;
    std::vector<Material*> m_materials;


    // All Mesh
    void StoreSceneAllVertices();
    // Specific data
    std::vector<float*> m_allVertices;
    std::array<float, 3> m_min;
    std::array<float, 3> m_max;
private:
    void LoadAiMesh(aiMesh* mesh, SubMesh* subMesh);

    Assimp::Importer m_importer;
    const aiScene* m_scene;
};