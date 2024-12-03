#pragma once

#include "Transform.h"

class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up);

    void UpdateViewMatrix();
    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix(float fov, float aspectRatio, float near, float far) const;

    void SetPosition(const glm::vec3& position);

    // Input
    void MoveForward(float amount);
    void Strafe(float amount);
    void Rotate(float xOffset, float yOffset);

private:
    glm::vec3 m_position;
    glm::vec3 m_target;
    glm::vec3 m_up;
    glm::mat4 m_view;

    // Temporaire

    Transform m_transform;

    float m_yaw;
    float m_pitch;

    const float m_sensitivity = 0.4f;
};
