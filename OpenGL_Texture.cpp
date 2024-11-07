#include "pch.h"

#include "OpenGL_Texture.h"

OpenGL_Texture::OpenGL_Texture(const char* filePath) {
    LoadTexture(filePath);
}

OpenGL_Texture::~OpenGL_Texture() {
    // Libération de la texture
    glDeleteTextures(1, &m_textureID);
}

void OpenGL_Texture::Bind(GLuint slot) const {
    //glActiveTexture(GL_TEXTURE0 + slot); // Activer le slot de texture
    //glBindTexture(GL_TEXTURE_2D, m_textureID); // Lier la texture
}

void OpenGL_Texture::LoadTexture(const char* filePath) {
    std::string fullPath = "res/models/dodge/";
    fullPath += filePath;

    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);


    std::cout << "Texture ID in GPU: " << m_textureID << std::endl;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);


        //std::cout << "Texture loaded successfully: " << fullPath << std::endl;
        //std::cout << "Width: " << width << ", Height: " << height << ", Channels: " << nrChannels << std::endl;
    }
    else {
        std::cerr << "Failed to load texture: " << fullPath << std::endl;
    }

    stbi_image_free(data);
}