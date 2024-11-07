#pragma once

#include "Material.h"
#include "Texture.h"
#include "Mesh.h"

#include "OpenGL_Material.h"
#include "OpenGL_Texture.h"
#include "OpenGL_Mesh.h"

template<typename T>
class ResourceManager {
public:
    virtual ~ResourceManager() {
        for (auto& resource : m_resources) 
            delete resource; 
    }

    inline int AddResource(T* resource) { 
        m_resources.push_back(resource); 
        return static_cast<int>(m_resources.size() - 1); 
    
    }
    inline T* GetResource(int id) { 
        return (id >= 0 && id < m_resources.size()) ? m_resources[id] : nullptr; 
    }
    inline void RemoveResource(int id) {
        if (id >= 0 && id < m_resources.size()) {
            delete m_resources[id];
            m_resources.erase(m_resources.begin() + id);
        } 
    }

    //inline IncrementSlot() { m_curSlotID++; };
    //int m_curSlotID = 0;

protected:
    std::vector<T*> m_resources;

};

class OpenGL_ResourceManager {
public:
    static OpenGL_ResourceManager& GetInstance() {
        static OpenGL_ResourceManager instance;
        return instance;
    }

    inline int AddMesh(OpenGL_Mesh* mesh) { return m_meshManager.AddResource(mesh);  }
    inline int AddMaterial(OpenGL_Material* material) { return m_materialManager.AddResource(material); }
    inline int AddTexture(OpenGL_Texture* texture) { 
        return m_textureManager.AddResource(texture); 
    }

    inline OpenGL_Mesh* GetMesh(int id) { return m_meshManager.GetResource(id); }
    inline OpenGL_Material* GetMaterial(int id) { return m_materialManager.GetResource(id); }
    inline OpenGL_Texture* GetTexture(int id) { return m_textureManager.GetResource(id); }

    inline void RemoveMesh(int id) { m_meshManager.RemoveResource(id); }
    inline void RemoveMaterial(int id) { m_materialManager.RemoveResource(id); }
    inline void RemoveTexture(int id) { m_textureManager.RemoveResource(id); }

private:
    OpenGL_ResourceManager() = default;
    OpenGL_ResourceManager(const OpenGL_ResourceManager&) = delete; 
    OpenGL_ResourceManager& operator=(const OpenGL_ResourceManager&) = delete; 

    ResourceManager<OpenGL_Mesh> m_meshManager;
    ResourceManager<OpenGL_Material> m_materialManager;
    ResourceManager<OpenGL_Texture> m_textureManager;
};