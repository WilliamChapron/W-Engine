#pragma once

#include "Texture.h"

class OpenGLTexture : public Texture {
public:
    OpenGLTexture(const char* filePath);

    ~OpenGLTexture();

    void Bind(GLuint slot = 0) const;

private:
    GLuint textureID; 

    void LoadTexture(const char* filePath);
};

