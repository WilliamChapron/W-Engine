#pragma once

class Primitive;
class Shader;
class Material;
class Submesh;

class RenderableEntity
{
public:
    virtual ~RenderableEntity() = default;  

    virtual void Init() = 0;

    // Sub mesh ***
    std::vector<Submesh*>& GetSubMeshes() { return m_subMeshes; }
    inline Material* GetMaterialByID(int id) { return m_materials[id]; }

    inline void SetSubmeshes(const std::vector<Submesh*>& subMeshes) { for (Submesh* subMesh : subMeshes) { m_subMeshes.push_back(subMesh); } }
    inline void SetMaterials(const std::vector<Material*>& materials) { for (Material* material : materials) { m_materials.push_back(material); } }

    inline void AddSubmesh(Submesh* subMesh) { m_subMeshes.push_back(subMesh); };
    void AddMaterial(Material* material) { m_materials.push_back(material); };
protected:
    std::vector<Submesh*> m_subMeshes;
    std::vector<Material*> m_materials;
};

