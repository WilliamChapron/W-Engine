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
        float verticalOffset = -0.5f;

        vertices = {
            {{0.0f, 1.0f + verticalOffset, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.5f, 1.0f}},

            {{-0.5f, 0.0f + verticalOffset, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
            {{ 0.5f, 0.0f + verticalOffset, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
            {{ 0.5f, 0.0f + verticalOffset,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
            {{-0.5f, 0.0f + verticalOffset,  0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
        };

        indices = {
            0, 1, 2,  
            0, 2, 3, 
            0, 3, 4,  
            0, 4, 1,  

            1, 2, 3,  
            1, 3, 4   
        };
    }
};

class Cube : public Primitive {
public:
    void Init() override {
        vertices = {
            // Jaune
            {{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
            {{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
            {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
            {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

            // Vert
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
            {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
            {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},

            // Bleu
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
            {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
            {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

            // Rouge
            {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
            {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
            {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
            {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

            // Cyan
            {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
            {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
            {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},

            // Magenta
            {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
            {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
            {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
        };


        indices = {
            0, 1, 2, 0, 2, 3,    
            4, 5, 6, 4, 6, 7,    
            8, 9, 10, 8, 10, 11,  
            12, 13, 14, 12, 14, 15, 
            16, 17, 18, 16, 18, 19, 
            20, 21, 22, 20, 22, 23, 
        };
    }
};



class PrimitiveRectangle : public Primitive {
public:
    PrimitiveRectangle(float width, float height)
        : width(width), height(height) {
    }

    void Init() override {
        vertices = {
            {{-1.f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
            {{ 1.f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
            {{ 1.f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
            {{-1.f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

            {{-1.f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
            {{ 1.f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
            {{ 1.f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
            {{-1.f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},

            {{-1.f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
            {{-1.f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
            {{-1.f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
            {{-1.f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

            {{ 1.f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
            {{ 1.f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
            {{ 1.f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
            {{ 1.f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

            {{-1.f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
            {{ 1.f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
            {{ 1.f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
            {{-1.f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},

            {{-1.f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
            {{ 1.f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
            {{ 1.f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
            {{-1.f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
        };


        indices = {
            0, 1, 2, 0, 2, 3,    
            4, 5, 6, 4, 6, 7,     
            8, 9, 10, 8, 10, 11,  
            12, 13, 14, 12, 14, 15, 
            16, 17, 18, 16, 18, 19, 
            20, 21, 22, 20, 22, 23, 
        };
    }

private:
    float width;  
    float height; 
};






class Cylinder : public Primitive {
public:
    Cylinder(float radius, float height, unsigned int segments = 36) : radius(radius), height(height), segments(segments) {
    }

    void Init() override {
        float angleStep = 2.0f * 3.14159265359f / segments;
        float halfHeight = height / 2.0f;

        vertices.clear();

        for (unsigned int i = 0; i < segments; ++i) {
            float angle = i * angleStep;
            float x = radius * cos(angle);
            float z = radius * sin(angle);

            vertices.push_back({ {x, -halfHeight, z}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f} });

            vertices.push_back({ {x, halfHeight, z}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f} });
        }


        vertices.push_back({ {0.0f, -halfHeight, 0.0f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.5f, 1.0f} });
        vertices.push_back({ {0.0f, halfHeight, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.5f, 0.0f} });


        indices.clear();

        for (unsigned int i = 0; i < segments; ++i) {
            unsigned int next = (i + 1) % segments;
            indices.push_back(i * 2); 
            indices.push_back(next * 2); 
            indices.push_back(segments * 2); 
        }

        for (unsigned int i = 0; i < segments; ++i) {
            unsigned int next = (i + 1) % segments;
            indices.push_back(i * 2 + 1); 
            indices.push_back(next * 2 + 1); 
            indices.push_back(segments * 2 + 1); 
        }

        for (unsigned int i = 0; i < segments; ++i) {
            unsigned int next = (i + 1) % segments;
            indices.push_back(i * 2); 
            indices.push_back(i * 2 + 1); 
            indices.push_back(next * 2 + 1); 

            indices.push_back(i * 2); 
            indices.push_back(next * 2 + 1); 
            indices.push_back(next * 2); 
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
        const int segments = 36;  
        const float verticalOffset = -0.5f; 

        vertices.push_back({ {0.0f, height + verticalOffset, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.5f, 1.0f} });


        for (int i = 0; i < segments; ++i) {
            float angle = (2.0f * 3.14159f * i) / segments; 
            float x = radius * cos(angle);
            float z = radius * sin(angle);
            vertices.push_back({ {x, verticalOffset, z}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f} });
        }

        for (int i = 1; i < segments; ++i) {
            indices.push_back(0);  
            indices.push_back(i);  
            indices.push_back(i + 1); 
        }
        indices.push_back(0);  
        indices.push_back(segments);  
        indices.push_back(1); 

        for (int i = 1; i < segments - 1; ++i) {
            indices.push_back(i);  
            indices.push_back(i + 1); 
            indices.push_back(segments); 
        }
        indices.push_back(segments - 1);  
        indices.push_back(1); 
        indices.push_back(segments); 
    }

private:
    float radius;
    float height;
};