#pragma once

#include "Mesh.h" 

class OpenGL_Mesh : public Mesh {
public:
    OpenGL_Mesh();
    ~OpenGL_Mesh();

    void Setup(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) override;
    void Update() override;

    unsigned int GetVAO() const { return VAO; }
    unsigned int GetIndexCount() const { return static_cast<unsigned int>(m_indices.size()); }

private:
    void SetupMesh();

    unsigned int VAO, VBO, EBO;
};
