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

void OpenGL_SubMesh::Setup(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, int materialID) {
    m_vertices = vertices;
    m_indices = indices;
    SetupBinding();
    SetMaterialID(materialID);
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