#pragma once

class Material;
class Submesh;

class GLTFLoader {
public:
    GLTFLoader() = default;

    void LoadFile(const std::string& filePath);

    std::vector<Submesh*> m_subMeshes;
    std::vector<Material*> m_materials;




    // All Mesh
    void StoreSceneAllVertices();
    // Specific data
    std::vector<float*> m_allVertices;
    std::array<float, 3> m_min;
    std::array<float, 3> m_max;


private:
    void LoadAiMesh(aiMesh* mesh, Submesh* subMesh);

    Assimp::Importer m_importer;
    const aiScene* m_scene;
};