#include "pch.h"
#include "Transform.h"

Transform::Transform() : m_position(0.0f), m_rotation(0.0f), m_scale(1.0f), m_worldMatrix(glm::mat4(1.0f))
{
}

Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) : m_position(position), m_rotation(rotation), m_scale(scale), m_worldMatrix(glm::mat4(1.0f))
{
}

void Transform::SetPosition(const glm::vec3& position) {
    m_position = position;
    UpdateWorldMatrix();
}

void Transform::SetRotation(const glm::vec3& rotation) {
    m_rotation = rotation;
    UpdateWorldMatrix();
}

void Transform::SetScale(const glm::vec3& scale) {
    m_scale = scale;
    UpdateWorldMatrix();
}

void Transform::UpdateVectors() {
    glm::mat4 rotationMatrix = glm::mat4_cast(glm::quat(glm::radians(m_rotation)));

    m_forward = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));
    m_right = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)));
    m_up = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)));

    // Affichage des vecteurs
    //std::cout << "Forward: (" << m_forward.x << ", " << m_forward.y << ", " << m_forward.z << ")\n";
    //std::cout << "Right: (" << m_right.x << ", " << m_right.y << ", " << m_right.z << ")\n";
    //std::cout << "Up: (" << m_up.x << ", " << m_up.y << ", " << m_up.z << ")\n";
}

void Transform::UpdateWorldMatrix() {
    glm::mat4 world = glm::mat4(1.0f);

    float pitch = glm::radians(m_rotation.x);
    float yaw = glm::radians(m_rotation.y);
    float roll = glm::radians(m_rotation.z);

    glm::quat quaternionX = glm::angleAxis(pitch, glm::vec3(1, 0, 0));
    glm::quat quaternionY = glm::angleAxis(yaw, glm::vec3(0, 1, 0));
    glm::quat quaternionZ = glm::angleAxis(roll, glm::vec3(0, 0, 1));

    glm::quat combinedQuaternion = quaternionZ * quaternionY * quaternionX;

    glm::mat4 rotationMatrix = glm::mat4_cast(combinedQuaternion);

    world = glm::translate(world, m_position);
    world = world * rotationMatrix;
    world = glm::scale(world, m_scale);

    m_worldMatrix = world;

    UpdateVectors();
}
