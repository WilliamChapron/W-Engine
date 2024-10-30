#include "pch.h"
#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up) : m_position(position), m_target(target), m_up(up) {
    UpdateViewMatrix();
}

void Camera::UpdateViewMatrix() {
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
    UpdateViewMatrix();
}
