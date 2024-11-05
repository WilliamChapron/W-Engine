#pragma once

class OpenGLTexture {
public:
    // Constructeur qui charge la texture à partir d'un fichier
    OpenGLTexture(const char* filePath);

    // Destructeur qui libère la texture
    ~OpenGLTexture();

    // Méthode pour lier la texture
    void Bind(GLuint slot = 0) const;

private:
    GLuint textureID; // ID de la texture OpenGL

    // Méthode pour charger la texture
    void LoadTexture(const char* filePath);
};

