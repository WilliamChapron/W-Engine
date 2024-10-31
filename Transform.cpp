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
    // Matrice d'identité
    glm::mat4 world = glm::mat4(1.0f);

    // Conversion des angles d'Euler en radians
    float pitch = glm::radians(m_Rotation.x); // Rotation autour de l'axe X
    float yaw = glm::radians(m_Rotation.y);   // Rotation autour de l'axe Y
    float roll = glm::radians(m_Rotation.z);  // Rotation autour de l'axe Z

    // Création d'un quaternion à partir des angles d'Euler
    glm::quat quaternionX = glm::angleAxis(pitch, glm::vec3(1, 0, 0)); // Rotation autour de X
    glm::quat quaternionY = glm::angleAxis(yaw, glm::vec3(0, 1, 0));   // Rotation autour de Y
    glm::quat quaternionZ = glm::angleAxis(roll, glm::vec3(0, 0, 1));  // Rotation autour de Z

    // Combinaison des quaternions
    glm::quat combinedQuaternion = quaternionZ * quaternionY * quaternionX; // Notez l'ordre

    // Conversion du quaternion en matrice de rotation
    glm::mat4 rotationMatrix = glm::mat4_cast(combinedQuaternion);

    // Appliquer la transformation complète
    world = glm::translate(world, m_Position); // Appliquer la translation
    world = world * rotationMatrix; // Appliquer la rotation

    // Appliquer l'échelle
    world = glm::scale(world, m_Scale);

    return world;
}