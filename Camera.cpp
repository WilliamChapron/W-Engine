#include "pch.h"
#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up)
    : m_position(position), m_target(target), m_up(up), m_yaw(-90.0f), m_pitch(0.0f) {
    m_transform.SetPosition(position);
    m_transform.SetRotation(glm::vec3(m_pitch, m_yaw, 0.0f)); // Initialisation de la rotation
}

void Camera::UpdateViewMatrix() {
    // Calcule le nouveau "target" à partir des rotations (pitch et yaw)
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_target = m_position + glm::normalize(front);

    // Met à jour la matrice de vue
    m_view = glm::lookAt(m_position, m_target, m_up);
}

glm::mat4 Camera::GetViewMatrix() const {
    return m_view;
}

glm::mat4 Camera::GetProjectionMatrix(float fov, float aspectRatio, float nearClip, float farClip) const {
    return glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
}

void Camera::SetPosition(const glm::vec3& position) {
    m_position = position;
    m_transform.SetPosition(position);
}

// Déplacer la caméra
void Camera::MoveForward(float amount) {
    glm::vec3 front = glm::normalize(m_target - m_position);  // Direction avant
    m_position += amount * front;
    m_transform.SetPosition(m_position);
}

void Camera::Strafe(float amount) {
    glm::vec3 right = glm::normalize(glm::cross(m_up, m_target - m_position));  // Direction droite
    m_position -= amount * right;
    m_transform.SetPosition(m_position);
}

void Camera::Rotate(float xOffset, float yOffset) {
    xOffset *= m_sensitivity;
    yOffset *= m_sensitivity;

    m_yaw += xOffset;
    m_pitch += yOffset;

    // Limites sur le pitch pour éviter un flip de la caméra
    if (m_pitch > 89.0f)
        m_pitch = 89.0f;
    if (m_pitch < -89.0f)
        m_pitch = -89.0f;

    // Appliquer la rotation directement à la transformation de la caméra
    m_transform.SetRotation(glm::vec3(m_pitch, m_yaw, 0.0f));

    // Recalcule la matrice de vue après la rotation
    UpdateViewMatrix();
}