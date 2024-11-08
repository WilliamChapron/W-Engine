#include "pch.h"
#include "Transform.h"

Transform::Transform() : m_Position(0.0f), m_Rotation(0.0f), m_Scale(1.0f), m_WorldMatrix(glm::mat4(1.0f)) {}

Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
    : m_Position(position), m_Rotation(rotation), m_Scale(scale), m_WorldMatrix(glm::mat4(1.0f)) {}

void Transform::SetPosition(const glm::vec3& position) {
    m_Position = position;
    UpdateWorldMatrix();
}

void Transform::SetRotation(const glm::vec3& rotation) {
    m_Rotation = rotation;
    UpdateWorldMatrix();
}

void Transform::SetScale(const glm::vec3& scale) {
    m_Scale = scale;
    UpdateWorldMatrix();
}

glm::vec3 Transform::GetPosition() const {
    return m_Position;
}

glm::vec3 Transform::GetRotation() const {
    return m_Rotation;
}

glm::vec3 Transform::GetScale() const {
    return m_Scale;
}

glm::mat4 Transform::GetTransformMatrix() const {
    return m_WorldMatrix;
}

void Transform::UpdateWorldMatrix() {
    glm::mat4 world = glm::mat4(1.0f);

    float pitch = glm::radians(m_Rotation.x);
    float yaw = glm::radians(m_Rotation.y);
    float roll = glm::radians(m_Rotation.z);

    glm::quat quaternionX = glm::angleAxis(pitch, glm::vec3(1, 0, 0));
    glm::quat quaternionY = glm::angleAxis(yaw, glm::vec3(0, 1, 0));
    glm::quat quaternionZ = glm::angleAxis(roll, glm::vec3(0, 0, 1));

    glm::quat combinedQuaternion = quaternionZ * quaternionY * quaternionX;

    glm::mat4 rotationMatrix = glm::mat4_cast(combinedQuaternion);

    world = glm::translate(world, m_Position);
    world = world * rotationMatrix;
    world = glm::scale(world, m_Scale);

    m_WorldMatrix = world;
}