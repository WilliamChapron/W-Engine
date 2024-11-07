#pragma once

#include "Mesh.h" 

class Material;

#include  "SubMesh.h";

class OpenGL_Mesh : public Mesh {
public:
    OpenGL_Mesh();
    ~OpenGL_Mesh();

    void LoadPrimitive() override;
    void LoadFile(const std::string& filePath) override;

private:
    void AddSubMesh(SubMesh* subMesh);
    void AddMaterial(Material* texture);

    Assimp::Importer m_importer;
    const aiScene* m_scene;
};