#pragma once

#include "RenderStructures.h"

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
        float verticalOffset = -0.5f; // D�calage pour centrer la pyramide

        vertices = {
            // Sommet (pointe de la pyramide) d�plac�
            {{0.0f, 1.0f + verticalOffset, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.5f, 1.0f}},

            // Base de la pyramide (tous les sommets de la base sont �galement d�plac�s)
            {{-0.5f, 0.0f + verticalOffset, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
            {{ 0.5f, 0.0f + verticalOffset, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
            {{ 0.5f, 0.0f + verticalOffset,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
            {{-0.5f, 0.0f + verticalOffset,  0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
        };

        indices = {
            0, 1, 2,  // Face arri�re
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
        // D�finition des sommets du cube
        vertices = {
            // Face avant (Jaune)
            {{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
            {{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
            {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
            {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

            // Face arri�re (Vert)
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
            {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
            {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},

            // Face gauche (Bleu)
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
            {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
            {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

            // Face droite (Rouge)
            {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
            {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
            {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
            {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

            // Face haut (Cyan)
            {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
            {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
            {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},

            // Face bas (Magenta)
            {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
            {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
            {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
        };

        // D�finition des indices pour dessiner le cube (12 triangles)
        indices = {
            0, 1, 2, 0, 2, 3,     // Face avant
            4, 5, 6, 4, 6, 7,     // Face arri�re
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
        : width(width), height(height) {
    }

    void Init() override {
        // D�finition des sommets du cube
        vertices = {
            // Face avant
            {{-1.f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
            {{ 1.f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
            {{ 1.f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
            {{-1.f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

            // Face arri�re
            {{-1.f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
            {{ 1.f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
            {{ 1.f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
            {{-1.f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},

            // Faces lat�rales (gauche, droite, haut, bas)
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

        // D�finition des indices pour dessiner le cube (12 triangles)
        indices = {
            0, 1, 2, 0, 2, 3,     // Face avant
            4, 5, 6, 4, 6, 7,     // Face arri�re
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


















































class Cylinder : public Primitive {
public:
    Cylinder(float radius, float height, unsigned int segments = 36) : radius(radius), height(height), segments(segments) {
    }

    void Init() override {
        float angleStep = 2.0f * 3.14159265359f / segments;
        float halfHeight = height / 2.0f;

        vertices.clear();

        // Sommets de la base inf�rieure
        for (unsigned int i = 0; i < segments; ++i) {
            float angle = i * angleStep;
            float x = radius * cos(angle);
            float z = radius * sin(angle);

            // Ajout des sommets pour la base inf�rieure
            vertices.push_back({ {x, -halfHeight, z}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f} });

            // Ajout des sommets pour la base sup�rieure
            vertices.push_back({ {x, halfHeight, z}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f} });
        }

        // Sommets du centre de la base inf�rieure et sup�rieure
        vertices.push_back({ {0.0f, -halfHeight, 0.0f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.5f, 1.0f} });
        vertices.push_back({ {0.0f, halfHeight, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.5f, 0.0f} });

        // Indices pour dessiner le cylindre
        indices.clear();

        // Triangle pour la base inf�rieure
        for (unsigned int i = 0; i < segments; ++i) {
            unsigned int next = (i + 1) % segments;
            indices.push_back(i * 2); // Premier sommet
            indices.push_back(next * 2); // Deuxi�me sommet
            indices.push_back(segments * 2); // Centre de la base inf�rieure
        }

        // Triangle pour la base sup�rieure
        for (unsigned int i = 0; i < segments; ++i) {
            unsigned int next = (i + 1) % segments;
            indices.push_back(i * 2 + 1); // Premier sommet
            indices.push_back(next * 2 + 1); // Deuxi�me sommet
            indices.push_back(segments * 2 + 1); // Centre de la base sup�rieure
        }

        // Faces lat�rales du cylindre
        for (unsigned int i = 0; i < segments; ++i) {
            unsigned int next = (i + 1) % segments;
            indices.push_back(i * 2); // Sommet de la base inf�rieure
            indices.push_back(i * 2 + 1); // Sommet de la base sup�rieure
            indices.push_back(next * 2 + 1); // Prochain sommet de la base sup�rieure

            indices.push_back(i * 2); // Sommet de la base inf�rieure
            indices.push_back(next * 2 + 1); // Prochain sommet de la base sup�rieure
            indices.push_back(next * 2); // Prochain sommet de la base inf�rieure
        }
    }

private:
    float radius;
    float height;
    unsigned int segments;
};

class Cone : public Primitive {
public:
    Cone(float radius = 0.5f, float height = 1.0f) : radius(radius), height(height) {
    }

    void Init() override {
        const int segments = 36;  // Nombre de segments pour approximer un cercle
        const float verticalOffset = -0.5f; // D�calage vertical pour centrer le c�ne

        // Sommet de la pointe du c�ne (centr�)
        vertices.push_back({ {0.0f, height + verticalOffset, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.5f, 1.0f} });

        // Sommets de la base du c�ne
        for (int i = 0; i < segments; ++i) {
            float angle = (2.0f * 3.14159f * i) / segments; // Angle pour chaque segment
            float x = radius * cos(angle);
            float z = radius * sin(angle);
            vertices.push_back({ {x, verticalOffset, z}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f} });
        }

        // Cr�ation des indices pour dessiner les faces lat�rales
        for (int i = 1; i < segments; ++i) {
            // Triangle entre la pointe et les deux points adjacents de la base
            indices.push_back(0);  // Pointe
            indices.push_back(i);  // Sommet de la base (i)
            indices.push_back(i + 1); // Sommet de la base (i+1)
        }
        // Dernier triangle pour refermer la base
        indices.push_back(0);  // Pointe
        indices.push_back(segments);  // Dernier sommet de la base
        indices.push_back(1); // Premier sommet de la base

        // Cr�ation de la base du c�ne (cercle)
        for (int i = 1; i < segments - 1; ++i) {
            indices.push_back(i);  // Sommet de la base (i)
            indices.push_back(i + 1); // Sommet de la base (i+1)
            indices.push_back(segments); // Centre de la base
        }
        indices.push_back(segments - 1);  // Dernier sommet de la base
        indices.push_back(1); // Premier sommet de la base
        indices.push_back(segments); // Centre de la base
    }

private:
    float radius;
    float height;
};