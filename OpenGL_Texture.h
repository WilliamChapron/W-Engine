#pragma once

class OpenGLTexture {
public:
    // Constructeur qui charge la texture � partir d'un fichier
    OpenGLTexture(const char* filePath);

    // Destructeur qui lib�re la texture
    ~OpenGLTexture();

    // M�thode pour lier la texture
    void Bind(GLuint slot = 0) const;

private:
    GLuint textureID; // ID de la texture OpenGL

    // M�thode pour charger la texture
    void LoadTexture(const char* filePath);
};

