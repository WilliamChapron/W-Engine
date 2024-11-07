#pragma once

#include "RenderStructures.hpp"

class SubMesh {
public:
    SubMesh() {};

    virtual ~SubMesh() {}

    virtual void Update() = 0;



protected:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    int m_materialID; // material ID redirect to mesh materials array
};