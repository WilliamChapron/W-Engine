#include "pch.h"

#include "OpenGL_Texture.h"

OpenGLTexture::OpenGLTexture(const char* filePath) {
    LoadTexture(filePath);
}

OpenGLTexture::~OpenGLTexture() {
    // Libération de la texture
    glDeleteTextures(1, &textureID);
}

void OpenGLTexture::Bind(GLuint slot) const {
    glActiveTexture(GL_TEXTURE0 + slot); // Activer le slot de texture
    glBindTexture(GL_TEXTURE_2D, textureID); // Lier la texture
}

void OpenGLTexture::LoadTexture(const char* filePath) {
    glGenTextures(1, &textureID); // Générer un identifiant de texture
    glBindTexture(GL_TEXTURE_2D, textureID); // Lier la texture

    // Définir les paramètres de texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Charger l'image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        // Créer la texture à partir des données de l'image
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D); // Générer les mipmaps
    }
    else {
        std::cerr << "Failed to load texture: " << filePath << std::endl;
    }
    stbi_image_free(data); // Libérer les données de l'image chargée
}
