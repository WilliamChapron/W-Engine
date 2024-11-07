#pragma once

#include "Texture.h"

class OpenGL_Texture : public Texture {
public:
    OpenGL_Texture(const char* filePath);

    ~OpenGL_Texture();

    void Bind(GLuint slot = 0) const;

    void Test() override {};

    GLuint GetID() { return m_textureID; };



private:
    GLuint m_textureID; 

    void LoadTexture(const char* filePath);
};

