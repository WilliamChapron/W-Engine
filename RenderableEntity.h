#pragma once

class Primitive;
class Shader;
class Material;
class SubMesh;

class RenderableEntity
{
public:
    virtual ~RenderableEntity() = default;  

    virtual void Init() = 0;
    //virtual void Prepare() = 0;

    // Sub mesh ***
    std::vector<SubMesh*>& GetSubMeshes() { return m_subMeshes; }
    inline Material* GetMaterialByID(int id) { return m_materials[id]; }

    inline void SetSubMesh(const std::vector<SubMesh*>& subMeshes) { for (SubMesh* subMesh : subMeshes) { m_subMeshes.push_back(subMesh); } }
    inline void SetMaterials(const std::vector<Material*>& materials) { for (Material* material : materials) { m_materials.push_back(material); } }

    inline void AddSubMesh(SubMesh* subMesh) { m_subMeshes.push_back(subMesh); };
    void AddMaterial(Material* material) { m_materials.push_back(material); };
    //
protected:
    std::vector<SubMesh*> m_subMeshes;
    std::vector<Material*> m_materials;
};

