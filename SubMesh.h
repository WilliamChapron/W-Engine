#pragma once

#include "RenderStructures.h"

class Submesh {
public:
    Submesh() {};

    virtual ~Submesh() {}

    virtual void Update() = 0;

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
protected:
    int m_materialID; // material ID redirect to mesh materials array
};