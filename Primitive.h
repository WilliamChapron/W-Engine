#pragma once

#include "RenderStructures.hpp"

class Primitive {
public:
    std::vector<Vertex> vertices;  
    std::vector<unsigned int> indices;  

    virtual void Init() = 0;  
    virtual ~Primitive() {};
};


class Pyramid : public Primitive {
public:
    void Init() override {
        vertices = {
            // Sommet (pointe de la pyramide)
            {{0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.5f, 1.0f}},

            // Base de la pyramide
            {{-0.5f, 0.0f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
            {{ 0.5f, 0.0f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
            {{ 0.5f, 0.0f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
            {{-0.5f, 0.0f,  0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
        };


        indices = {
            0, 1, 2,  // Face arrière
            0, 2, 3,  // Face droite
            0, 3, 4,  // Face avant
            0, 4, 1,  // Face gauche

            1, 2, 3,  // Base
            1, 3, 4   // Base
        };
    }
};