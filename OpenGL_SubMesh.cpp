#include "pch.h"

#include "RenderStructures.hpp"

#include "OpenGL_SubMesh.h"
#include "OpenGL_Material.h"

OpenGL_SubMesh::OpenGL_SubMesh() : m_VAO(0), m_VBO(0), m_EBO(0) 
{
}

OpenGL_SubMesh::~OpenGL_SubMesh() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

void OpenGL_SubMesh::Setup(aiMesh* mesh) {
    LoadModel(mesh);
    SetupBinding();
}

void OpenGL_SubMesh::LoadModel(aiMesh* mesh) {
    for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
        Vertex vertex;
        vertex.position[0] = mesh->mVertices[j].x;
        vertex.position[1] = mesh->mVertices[j].y;
        vertex.position[2] = mesh->mVertices[j].z;

        if (mesh->mNormals) {
            vertex.normal[0] = mesh->mNormals[j].x;
            vertex.normal[1] = mesh->mNormals[j].y;
            vertex.normal[2] = mesh->mNormals[j].z;
        }

        if (mesh->mTextureCoords[0]) {
            vertex.texCoords[0] = mesh->mTextureCoords[0][j].x;
            vertex.texCoords[1] = mesh->mTextureCoords[0][j].y;
        }
        else {
            vertex.texCoords[0] = 0.0f;
            vertex.texCoords[1] = 0.0f;
        }

        m_vertices.push_back(vertex);
    }

    for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
        aiFace face = mesh->mFaces[j];
        for (unsigned int k = 0; k < face.mNumIndices; k++) {
            m_indices.push_back(face.mIndices[k]);
        }
    }
}

void OpenGL_SubMesh::LoadModel(const  std::vector<Vertex>& vertices,const std::vector<unsigned int>& indices) {
    m_vertices = vertices;
    m_indices = indices;
}

void OpenGL_SubMesh::SetupBinding() {
    // Generate and bind the Vertex Array Object (VAO)
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    // Bind and configure the vertex buffer (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

    // Bind and configure the index buffer (EBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    // Normals
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);

    // Texture coordinates
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(3);

    // Unbind the VBO and the VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void OpenGL_SubMesh::Prepare(OpenGL_Material* material) {

    glBindVertexArray(m_VAO);
}