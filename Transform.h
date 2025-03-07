#pragma once



class Transform {
public:
    Transform();
    Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);

    void SetPosition(const glm::vec3& position);
    void SetRotation(const glm::vec3& rotation);
    void SetScale(const glm::vec3& scale);

    inline glm::vec3 GetPosition() const { return m_position; }
    inline glm::vec3 GetRotation() const { return m_rotation; }
    inline glm::vec3 GetScale() const { return m_scale; }

    inline glm::vec3 GetForward() const { return m_forward; }
    inline glm::vec3 GetRight() const { return m_right; }
    inline glm::vec3 GetUp() const { return m_up; }

    glm::mat4 GetWorldMatrix() const { return m_worldMatrix; }

    glm::vec3 m_rotation;

private:
    void UpdateWorldMatrix();
    void UpdateVectors();

    glm::vec3 m_position;
    glm::vec3 m_scale;
    glm::mat4 m_worldMatrix;

    glm::vec3 m_forward;
    glm::vec3 m_right;
    glm::vec3 m_up;
};


