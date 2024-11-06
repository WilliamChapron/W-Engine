#pragma once

#include "RenderStructures.h"

class SubMesh {
public:
    SubMesh() {};

    virtual ~SubMesh() {}

    virtual void Update() = 0;

protected:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    int m_aText; // Albedo texture Index
};

// Add a range for offset gpu