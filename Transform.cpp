#include "pch.h"
#include "Transform.h"

Transform::Transform()
    : m_Position(0.0f), m_Rotation(0.0f), m_Scale(1.0f) {}

Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
    : m_Position(position), m_Rotation(rotation), m_Scale(scale) {}

void Transform::SetPosition(const glm::vec3& position) {
    m_Position = position;
}

void Transform::SetRotation(const glm::vec3& rotation) {
    m_Rotation = rotation;
}

void Transform::SetScale(const glm::vec3& scale) {
    m_Scale = scale;
}

glm::mat4 Transform::GetTransformMatrix() const {
    glm::mat4 world = glm::mat4(1.0f); // Identity matrix

    // Création des quaternions pour chaque axe de rotation
    glm::quat qX = glm::angleAxis(glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::quat qY = glm::angleAxis(glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::quat qZ = glm::angleAxis(glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    // Combinaison des quaternions
    glm::quat q = qZ * qY * qX;

    // Conversion du quaternion en matrice de rotation
    glm::mat4 rotationMatrix = glm::mat4_cast(q);

    // Appliquer la translation et l'échelle
    world = glm::translate(world, m_Position); // Appliquer la translation
    world = glm::scale(world, m_Scale); // Appliquer l'échelle
    world = rotationMatrix * world; // Appliquer la rotation

    return world;
}