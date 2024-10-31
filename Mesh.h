#pragma once

struct Vertex {
    float position[3];
    float color[4];
    float normal[3];
    float texCoords[2];
};

class Mesh {
public:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    virtual ~Mesh() {}

    virtual void Setup(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) = 0;
    virtual void Update() = 0; 
};
