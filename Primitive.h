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
        float verticalOffset = -0.5f; // Décalage pour centrer la pyramide

        vertices = {
            // Sommet (pointe de la pyramide) déplacé
            {{0.0f, 1.0f + verticalOffset, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.5f, 1.0f}},

            // Base de la pyramide (tous les sommets de la base sont également déplacés)
            {{-0.5f, 0.0f + verticalOffset, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
            {{ 0.5f, 0.0f + verticalOffset, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
            {{ 0.5f, 0.0f + verticalOffset,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
            {{-0.5f, 0.0f + verticalOffset,  0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
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

class Cube : public Primitive {
public:
    void Init() override {
        // Définition des sommets du cube
        vertices = {
            // Face avant
            {{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
            {{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
            {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
            {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

            // Face arrière
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
            {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
            {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},

            // Faces latérales (gauche, droite, haut, bas)
            // Gauche
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
            {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
            {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

            // Droite
            {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
            {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
            {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
            {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

            // Haut
            {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
            {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
            {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},

            // Bas
            {{-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
            {{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
            {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
        };

        // Définition des indices pour dessiner le cube (12 triangles)
        indices = {
            0, 1, 2, 0, 2, 3,     // Face avant
            4, 5, 6, 4, 6, 7,     // Face arrière
            8, 9, 10, 8, 10, 11,  // Face gauche
            12, 13, 14, 12, 14, 15, // Face droite
            16, 17, 18, 16, 18, 19, // Face haut
            20, 21, 22, 20, 22, 23, // Face bas
        };
    }
};


class PrimitiveRectangle : public Primitive {
public:
    PrimitiveRectangle(float width, float height)
        : width(width), height(height) {}

    void Init() override {
        // Définition des sommets du cube
        vertices = {
            // Face avant
            {{-1.f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
            {{ 1.f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
            {{ 1.f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
            {{-1.f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

            // Face arrière
            {{-1.f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
            {{ 1.f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
            {{ 1.f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
            {{-1.f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},

            // Faces latérales (gauche, droite, haut, bas)
            // Gauche
            {{-1.f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
            {{-1.f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
            {{-1.f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
            {{-1.f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

            // Droite
            {{ 1.f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
            {{ 1.f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
            {{ 1.f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
            {{ 1.f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

            // Haut
            {{-1.f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
            {{ 1.f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
            {{ 1.f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
            {{-1.f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},

            // Bas
            {{-1.f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
            {{ 1.f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
            {{ 1.f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
            {{-1.f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
        };

        // Définition des indices pour dessiner le cube (12 triangles)
        indices = {
            0, 1, 2, 0, 2, 3,     // Face avant
            4, 5, 6, 4, 6, 7,     // Face arrière
            8, 9, 10, 8, 10, 11,  // Face gauche
            12, 13, 14, 12, 14, 15, // Face droite
            16, 17, 18, 16, 18, 19, // Face haut
            20, 21, 22, 20, 22, 23, // Face bas
        };
    }

private:
    float width;  // Largeur du rectangle
    float height; // Hauteur du rectangle
};