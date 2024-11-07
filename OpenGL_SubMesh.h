#pragma once

#include "SubMesh.h" 

class OpenGL_Material;

class OpenGL_SubMesh : public SubMesh {
public:
    OpenGL_SubMesh();
    ~OpenGL_SubMesh();

    void Update() override {};
    unsigned int GetVAO() const { return m_VAO; }
    unsigned int GetIndexCount() const { return static_cast<unsigned int>(m_indices.size()); }

    void Setup(aiMesh* mesh);

    inline void SetMaterialID(int id) {m_materialID = id;}
    inline int GetMaterialID() { return m_materialID; }

    // Each frame
    void Prepare(OpenGL_Material* material);

private:
    void LoadModel(aiMesh* mesh);
    void SetupBinding();

    unsigned int m_VAO, m_VBO, m_EBO;
};