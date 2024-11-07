#pragma once

#include "RenderStructures.hpp"

class SubMesh {
public:
    SubMesh() {};

    virtual ~SubMesh() {}

    virtual void Update() = 0;

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
protected:
    int m_materialID; // material ID redirect to mesh materials array
};