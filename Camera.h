#pragma once

class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up);

    void UpdateViewMatrix();
    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix(float fov, float aspectRatio, float near, float far) const;

    void SetPosition(const glm::vec3& position);

private:
    glm::vec3 m_position;
    glm::vec3 m_target;
    glm::vec3 m_up;
    glm::mat4 m_view;
};
