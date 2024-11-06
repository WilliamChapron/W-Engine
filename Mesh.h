#pragma once

#include "RenderStructures.h"

class SubMesh;
class Texture;

class Mesh {
public:
    virtual ~Mesh() {};

    virtual void LoadPrimitive() = 0;
    virtual void LoadFile(const std::string& filePath) = 0;

    std::vector<SubMesh*>& GetSubMeshes() { return m_subMeshes; }
    std::vector<Texture*>& GetDiffuseTextures() { return m_diffuseTextures; }

protected:

    std::vector<SubMesh*> m_subMeshes;
    std::vector<Texture*> m_diffuseTextures;
};
