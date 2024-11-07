#pragma once

#include "RenderStructures.hpp"

class SubMesh;
class Texture;
class Material;

class Mesh {
public:
    virtual ~Mesh() {};

    virtual void LoadPrimitive() = 0;
    virtual void LoadFile(const std::string& filePath) = 0;

    std::vector<SubMesh*>& GetSubMeshes() { return m_subMeshes; }
    inline Material* GetMaterialByID(int id) { return m_materials[id]; }



protected:

    std::vector<SubMesh*> m_subMeshes;
    std::vector<Material*> m_materials;
};
