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
    //#IMPORTANT - Good order : translate->rotate->rescale !
    // -----------
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

    return world;
}